/*
 * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     LiuMingHang <liuminghang@uniontech.com>
 *
 * Maintainer: ZhangYong <ZhangYong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "application.h"

#include "controller/configsetter.h"
#include "controller/globaleventfilter.h"
#include "controller/signalmanager.h"
#include "controller/wallpapersetter.h"
#include "controller/viewerthememanager.h"
#include "utils/snifferimageformat.h"
#include "frame/mainwindow.h"

#include <QDebug>
#include <QTranslator>
#include <DApplicationSettings>
#include <QIcon>
#include <QPaintDevice>
#include <QImageReader>
#include <sys/time.h>
#include <QFile>
#include <QImage>
#include <QQueue>
#include <DVtableHook>
#include <DGuiApplicationHelper>
#include <DSysInfo>

#include "controller/commandline.h"
#include "service/ocrinterface.h"
#ifdef USE_UNIONIMAGE
#include "utils/unionimage.h"
#endif
namespace {

}  // namespace

//#define PIXMAP_LOAD //用于判断是否采用pixmap加载，qimage加载会有内存泄露
Application *Application::m_signalapp = nullptr;

ImageLoader::ImageLoader(Application *parent, const QStringList &pathlist, const QString &path)
    : m_parent(parent),
      m_pathlist(pathlist),
      m_path(path),
      m_bFlag(true)
{
}

void ImageLoader::startLoading()
{
    struct timeval tv;
    long long ms;
    gettimeofday(&tv, nullptr);
    ms = static_cast<long long>(tv.tv_sec) * 1000 + tv.tv_usec / 1000;
    qDebug() << "startLoading start time: " << ms;

    int num = 0;
    int array = 0;

    for (QString path : m_pathlist) {
        num++;
        if (m_path == path) {
            array = num - 1;
            num = 0;
        }
    }
    dApp->getRwLock().unlock();
    //heyi test
//    QStringList list;
//    for (int i = 0; i < 25; i++) {
//        if ((array - i) > -1) {
//            list.append(m_pathlist.at(array - i));
//        }
//        if ((array + i) < count) {
//            list.append(m_pathlist.at(array + i));
//        }
//    }
    listLoad1.clear();
    listLoad2.clear();
    //heyi test 开辟两个线程同时加载,重选中位置往两边加载
    for (int i = 0; i < array; i++) {
        listLoad1.append(m_pathlist.at(i));
    }
    //由于打开图片已经裁剪成缩略图所以不需要加载
    for (int i = array + 1; i < m_pathlist.size(); i++) {
        listLoad2.append(m_pathlist.at(i));
    }

    QThread *th1 = QThread::create([ = ]() {
        QString path;
        while (1) {
            path.clear();
            m_readlock.lockForWrite();
            if (listLoad1.isEmpty()) {
                m_readlock.unlock();
                break;
            }

            //判断线程标识
            if (!m_bFlag) {
                m_readlock.unlock();
                break;
            }

            path = listLoad1.back();
//            qDebug() << "线程1当前加载的图片：" << path;
            //加载完成之后删除该图片路径
            listLoad1.pop_back();
            m_readlock.unlock();
            loadInterface(path);
        }

        //帮助另一个线程加载，从左往右加载
        while (1) {
            path.clear();
            m_readlock.lockForWrite();
            if (listLoad2.isEmpty()) {
                m_readlock.unlock();
                break;
            }

            //判断线程标识
            if (!m_bFlag) {
                m_readlock.unlock();
                break;
            }

            path = listLoad2.front();
//            qDebug() << "线程1当前加载的图片：" << path;
            listLoad2.pop_front();
            m_readlock.unlock();
            loadInterface(path);
        }
        qDebug() << "th1" << QThread::currentThreadId();
        QThread::currentThread()->quit();
    });

    QThread *th2 = QThread::create([ = ]() {
        QString path;
        while (1) {
            path.clear();
            m_readlock.lockForWrite();
            if (listLoad2.isEmpty()) {
                m_readlock.unlock();
                break;
            }

            //判断线程标识
            if (!m_bFlag) {
                m_readlock.unlock();
                break;
            }

            m_flagLock.unlock();

            path = listLoad2.front();
//            qDebug() << "线程2当前加载的图片：" << path;
            //加载完成之后删除该图片路径
            listLoad2.pop_front();
            m_readlock.unlock();
            loadInterface(path);
        }

        //帮助另一个线程加载，从右往左加载
        while (1) {
            path.clear();
            m_readlock.lockForWrite();
            if (listLoad1.isEmpty()) {
                m_readlock.unlock();
                break;
            }

            //判断线程标识
            if (!m_bFlag) {
                m_readlock.unlock();
                break;
            }


            path = listLoad1.back();
            qDebug() << "线程2当前加载的图片：" << path;
            listLoad1.pop_back();
            m_readlock.unlock();
            loadInterface(path);
        }
        qDebug() << QThread::currentThreadId();
        QThread::currentThread()->quit();
    });
    connect(th1, &QThread::finished, th1, &QObject::deleteLater);
    connect(th2, &QThread::finished, th2, &QObject::deleteLater);
    th1->start();
    th2->start();

    QString map = "";
    emit sigFinishiLoad(map);

    gettimeofday(&tv, nullptr);
    ms = static_cast<long long>(tv.tv_sec) * 1000 + tv.tv_usec / 1000;
    QThread::currentThread()->quit();
}

void ImageLoader::stopThread()
{
    m_bFlag = false;
}

//void ImageLoader::addImageLoader(QStringList pathlist)
//{
//    /*lmh0724使用USE_UNIONIMAGE*/
//#if USE_UNIONIMAGE
//    for (QString path : pathlist) {

//        QImage tImg;
//        QString errMsg;
//        if (!UnionImage_NameSpace::loadStaticImageFromFile(path, tImg, errMsg)) {
//            qDebug() << errMsg;
//        }
//        //LMH0601加锁
//        QMutexLocker lcoker(&dApp->getRwLock());
//        QPixmap pixmap = QPixmap::fromImage(tImg);
//        m_parent->m_imagemap.insert(path, pixmap.scaledToHeight(IMAGE_HEIGHT_DEFAULT,  Qt::SmoothTransformation));
//    }
//#else


//    for (QString path : pathlist) {

//        QImage tImg;

//        QString format = DetectImageFormat(path);
//        if (format.isEmpty()) {
//            QImageReader reader(path);
//            reader.setAutoTransform(true);
//            if (reader.canRead()) {
//                tImg = reader.read();
//            }
//        } else {
//            QImageReader readerF(path, format.toLatin1());
//            readerF.setAutoTransform(true);
//            if (readerF.canRead()) {
//                tImg = readerF.read();
//            } else {
//                qWarning() << "can't read image:" << readerF.errorString()
//                           << format;

//                tImg = QImage(path);
//            }
//        }
//        //LMH0601加锁
//        QMutexLocker(&dApp->getRwLock());
//        //dApp->getRwLock().lockForWrite();
//        QPixmap pixmap = QPixmap::fromImage(tImg);

//        m_parent->m_imagemap.insert(path, pixmap.scaledToHeight(IMAGE_HEIGHT_DEFAULT,  Qt::FastTransformation));
//        //dApp->getRwLock().unlock();
//    }
//        #endif

//}
//modify by heyi
void ImageLoader::updateImageLoader(QStringList pathlist, bool bDirection, int rotateangle)
{
    for (QString path : pathlist) {
        QMutexLocker locker(&dApp->getRwLock());
//        dApp->getRwLock().lockForWrite();
        QPixmap pixmap = m_parent->m_imagemap[path];
        if (pixmap.isNull()) {
            QImage image(path);
            pixmap = QPixmap::fromImage(image);
        } else {
            QMatrix rotate;
            if (bDirection) {
                rotate.rotate(rotateangle);
            } else {
                rotate.rotate(0 - rotateangle);
            }

            pixmap = pixmap.transformed(rotate, Qt::FastTransformation);
        }

        //QImage image(path);
        //QPixmap pixmap = QPixmap::fromImage(image);
        m_parent->m_imagemap[path] = pixmap.scaledToHeight(IMAGE_HEIGHT_DEFAULT,  Qt::FastTransformation);
        // dApp->getRwLock().unlock();
    }
}

void ImageLoader::loadInterface(QString path)
{
    /*lmh0724使用USE_UNIONIMAGE*/
#ifdef USE_UNIONIMAGE
    //切换到按照图片的比例加载缩略图
    QImageReader reader(path);
    int height = reader.size().height();
    int width = reader.size().width();
    double w = 1;
    if (height != 0 && width != 0) {
        w = static_cast <double>(width) / static_cast <double>(height);
    }
    double dWidth;
    double dHeight;

    dWidth = IMAGE_HEIGHT_DEFAULT * w;
    dHeight = IMAGE_HEIGHT_DEFAULT ;
    if (dWidth > 300) {
        dWidth = 300;
        dHeight = 300 / w;
    }
    if (w <= 0) {
        dWidth = IMAGE_HEIGHT_DEFAULT;
        dHeight = IMAGE_HEIGHT_DEFAULT;
    }

    QImage tImg(static_cast<int>(dWidth), static_cast<int>(dHeight), QImage::Format_RGB32);
    QString errMsg;
    QSize realSize;
    if (!UnionImage_NameSpace::loadStaticImageFromFile(path, tImg, realSize, errMsg)) {
        qDebug() << errMsg;
    }
    /*lmh0728线程pixmap安全问题*/
    //wzy0608当loadStaticImageFromFile的快速加载生效时，不重复缩放图片
    if (tImg.height() != IMAGE_HEIGHT_DEFAULT) {
        tImg = tImg.scaledToHeight(IMAGE_HEIGHT_DEFAULT,  Qt::SmoothTransformation);
    }
    QPixmap pixmap = QPixmap::fromImage(tImg);
#else
    QImage tImg;
    QString format = DetectImageFormat(path);
    if (format.isEmpty()) {
        QImageReader reader(path);
        reader.setAutoTransform(true);
        if (reader.canRead()) {
            tImg = reader.read();
        }
    } else {
        QImageReader readerF(path, format.toLatin1());
        readerF.setAutoTransform(true);
        if (readerF.canRead()) {
            tImg = readerF.read();
        } else {
            qWarning() << "can't read image:" << readerF.errorString()
                       << format;

            tImg = QImage(path);
        }
    }

    QPixmap pixmap = QPixmap::fromImage(tImg);
#endif
    QMutexLocker locker(&dApp->getRwLock());
    //m_parent->m_rectmap.insert(path, tImg.rect());
    m_parent->m_rectmap.insert(path, QRect(0, 0, realSize.width(), realSize.height()));
    m_parent->m_imagemap.insert(path, pixmap);
    // dApp->getRwLock().unlock();

    emit sigFinishiLoad(path);
}

void Application::finishLoadSlot(const QString &mapPath)
{
    emit sigFinishLoad(mapPath);
}

void Application::loadPixThread(const QStringList &paths)
{
//fix 52217  shuwenzhi
    //m_loadPaths = paths;

    //开启线程进行后台加载图片

    QThread *th = QThread::create([ = ]() {

        QStringList pathList = paths;

        foreach (QString var, pathList) {
            if (m_bThreadExit) {
                break;
            }

            loadInterface(var);
        }

        //发送动态加载完成信号
        emit dynamicLoadFinished();

        QThread::currentThread()->quit();

    });

    connect(th, &QThread::finished, th, &QObject::deleteLater);
    th->start();
}

void Application::loadInterface(QString path)
{
    QMutexLocker locker(&dApp->getRwLock());
    //  dApp->getRwLock().lockForWrite();
#ifdef USE_UNIONIMAGE
    QImage tImg;
    QString errMsg;
    QSize realSize;
    if (!UnionImage_NameSpace::loadStaticImageFromFile(path, tImg, realSize, errMsg)) {
        qDebug() << errMsg;
    }
    if (tImg.height() != IMAGE_HEIGHT_DEFAULT) {
        tImg = tImg.scaledToHeight(IMAGE_HEIGHT_DEFAULT,  Qt::SmoothTransformation);
    }
    QPixmap pixmap = QPixmap::fromImage(tImg);
#else
    QImage tImg;
    QString format = DetectImageFormat(path);
    if (format.isEmpty()) {
        QImageReader reader(path);
        reader.setAutoTransform(true);
        if (reader.canRead()) {
            tImg = reader.read();
        }
    } else {
        QImageReader readerF(path, format.toLatin1());
        readerF.setAutoTransform(true);
        if (readerF.canRead()) {
            tImg = readerF.read();
        } else {
            qWarning() << "can't read image:" << readerF.errorString()
                       << format;

            tImg = QImage(path);
        }
    }

    QPixmap pixmap = QPixmap::fromImage(tImg);
#endif
    //m_rectmap.insert(path, tImg.rect());
    m_rectmap.insert(path, QRect(0, 0, realSize.width(), realSize.height()));
    m_imagemap.insert(path, pixmap);
    // dApp->getRwLock().unlock();

    finishLoadSlot(path);
}

Application *Application::instance(int &argc, char **argv)
{

    if (m_signalapp == nullptr) {
        m_signalapp = new Application(argc, argv);
    }
    return m_signalapp;
}

Application *Application::getinstance()
{
    return m_signalapp;
}

void Application::sendOcrPicture(const QImage &img, const QString &path)
{
    //图片过大，会导致崩溃，超过4K，智能裁剪
    if (m_ocrInterface != nullptr) {
        QImage image = img;
        if (image.width() > 5000) {
            image = image.scaledToWidth(5000, Qt::SmoothTransformation);
        }
        if (image.height() > 5000) {
            image = image.scaledToHeight(5000, Qt::SmoothTransformation);
        }
        QFileInfo info(path);
        //采用路径，以防止名字出错
        m_ocrInterface->openImageAndName(image, path);
    }
}

Application::Application(int &argc, char **argv)
{
    //判断DTK版本是否支持Deepin-turbo优化
#if (DTK_VERSION < DTK_VERSION_CHECK(5, 4, 0, 0))
    m_app = new DApplication(argc, argv);
#else
    m_app = DApplication::globalApplication(argc, argv);
    //判断DTK版本是否支持平板适配
#if (DTK_VERSION >= DTK_VERSION_CHECK(5, 5, 0, 0))
    m_bIsPanel = Dtk::Gui::DGuiApplicationHelper::isTabletEnvironment();
#else
    m_bIsPanel = false;
#endif

#endif
    Dtk::Core::DVtableHook::overrideVfptrFun(m_app, &DApplication::handleQuitAction, this, &Application::quitApp);
    m_LoadThread = nullptr;
    m_app->setOrganizationName("deepin");
    m_app->setApplicationName("deepin-image-viewer");
    initI18n();
    m_app->setApplicationDisplayName(tr("Image Viewer"));
    m_app->setProductIcon(QIcon::fromTheme("deepin-image-viewer"));
//    setApplicationDescription(QString("%1\n%2\n").arg(tr("看图是⼀款外观时尚，性能流畅的图片查看工具。")).arg(tr("看图是⼀款外观时尚，性能流畅的图片查看工具。")));
//    setApplicationAcknowledgementPage("https://www.deepin.org/" "acknowledgments/deepin-image-viewer/");
    m_app->setApplicationDescription(tr("Image Viewer is an image viewing tool with fashion interface and smooth performance."));

//    //save theme
//    DApplicationSettings saveTheme;

//    setApplicationVersion(DApplication::buildVersion("1.3"));

    m_app->setApplicationVersion(DApplication::buildVersion("5.7.10"));
    installEventFilter(new GlobalEventFilter());


    initChildren();



    connect(signalM, &SignalManager::sendPathlist, this, [ = ](QStringList list, QString path) {
//        if(m_LoadThread && m_LoadThread->isRunning()){
//            emit endThread();
//            QThread::msleep(500);

//        }
        m_imageloader = new ImageLoader(this, list, path);
        m_LoadThread = new QThread();

        m_imageloader->moveToThread(m_LoadThread);
        //在线程中调用了quit()　会处罚finished信号，　链接此槽函数，会销毁对象，而其他地方在判断对象是否还在运行容易崩溃。
        //  connect(m_LoadThread, &QThread::finished, m_LoadThread, &QObject::deleteLater);

        connect(this, SIGNAL(sigstartLoad()), m_imageloader, SLOT(startLoading()));
        connect(m_imageloader, SIGNAL(sigFinishiLoad(QString)), this, SLOT(finishLoadSlot(QString)));
        //heyi
        connect(this, SIGNAL(endThread()), m_imageloader, SLOT(stopThread()), Qt::QueuedConnection);

        m_LoadThread->start();




        emit sigstartLoad();
    });
    Dtk::Core::DSysInfo::UosEdition edition =  Dtk::Core::DSysInfo::uosEditionType();
    m_isEuler =  Dtk::Core::DSysInfo::UosEuler == edition || Dtk::Core::DSysInfo::UosEnterpriseC == edition;

    if (!m_ocrInterface) {
        m_ocrInterface = new OcrInterface("com.deepin.Ocr", "/com/deepin/Ocr", QDBusConnection::sessionBus(), this);
    }
}
bool Application::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        emit sigMouseRelease();
    }
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        // tab键 交互处理
        if (keyEvent->key() == Qt::Key_Tab) {
            emit TabkeyPress(obj);
        }
    }
    return QObject::eventFilter(obj, event);
}

void Application::setIsApplePhone(bool iRet)
{
    m_isapplePhone = iRet;
}

bool Application::IsApplePhone()
{
    return m_isapplePhone;
}

void Application::setIsOnlyOnePic(bool iRet)
{
    m_isOnlyOnePic = iRet;
}

bool Application::IsOnlyOnePic()
{
    return m_isOnlyOnePic;
}

bool Application::isEuler()
{
    return m_isEuler;
}

void Application::initChildren()
{
    viewerTheme = ViewerThemeManager::instance();
    setter = ConfigSetter::instance();
    signalM = SignalManager::instance();
    wpSetter = WallpaperSetter::instance();
}

void Application::initI18n()
{
    // install translators
    //    QTranslator *translator = new QTranslator;
    //    translator->load(APPSHAREDIR"/translations/deepin-image-viewer_"
    //                     + QLocale::system().name() + ".qm");
    //    installTranslator(translator);
    m_app->loadTranslator(QList<QLocale>() << QLocale::system());
}

Application::~Application()
{
    //隐藏详细信息
    emit signalM->hideExtensionPanel();
    if (nullptr !=  m_LoadThread) {
        if (m_LoadThread->isRunning()) {
            //结束线程
            m_LoadThread->requestInterruption();
            m_bThreadExit = true;
            emit endThread();
            QThread::msleep(1000);
            m_LoadThread->quit();
        }
    }

    emit endApplication();
}

void Application::quitApp()
{
    MainWindow *mainwindow = CommandLine::instance()->getMainWindow();
    mainwindow->close();
}
