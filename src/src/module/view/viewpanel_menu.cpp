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
#include <DMenu>
#include <QJsonArray>
#include <QJsonDocument>
#include <QKeySequence>
#include <QShortcut>
#include <QStyleFactory>
#include "application.h"
#include "contents/imageinfowidget.h"
#include "controller/configsetter.h"
#include "controller/wallpapersetter.h"
#include "navigationwidget.h"
#include "scen/imageview.h"
#include "utils/baseutils.h"
#include "utils/imageutils.h"
#include "viewpanel.h"
#include "widgets/printhelper.h"

namespace {
//LMH0603删除按键延迟
const int DELAY_DESTROY_TIME = 500;
const int DELAY_HIDE_CURSOR_INTERVAL = 3000;
// const QSize ICON_SIZE = QSize(48, 40);

}  // namespace

namespace {

const int SWITCH_IMAGE_DELAY = 200;
const QString SHORTCUTVIEW_GROUP = "SHORTCUTVIEW";
const QString FAVORITES_ALBUM_NAME = "My favorite";

QString ss(const QString &text, const QString &defaultValue)
{
    Q_UNUSED(text);
    //采用代码中快捷键不使用配置文件快捷键
    // QString str = dApp->setter->value(SHORTCUTVIEW_GROUP, text, defaultValue).toString();
    QString str = defaultValue;
    str.replace(" ", "");
    return defaultValue;
}



}  // namespace

void ViewPanel::initPopupMenu()
{
    QShortcut *ctrlm = new QShortcut(QKeySequence("Ctrl+M"), this);
    ctrlm->setContext(Qt::WindowShortcut);
    connect(ctrlm, &QShortcut::activated, this, [ = ] {
        this->customContextMenuRequested(cursor().pos());
    });
    if (!dApp->isPanelDev()) {
        m_menu = new DMenu;
        connect(this, &ViewPanel::customContextMenuRequested, this, [ = ] {
            if (m_infos.isEmpty())
                return;
            QString filePath = m_infos.at(m_current).filePath;
#ifdef LITE_DIV
            if (!filePath.isEmpty() && QFileInfo(filePath).exists())
#endif
            {
                updateMenuContent();
                dApp->m_app->setOverrideCursor(Qt::ArrowCursor);
                m_menu->popup(QCursor::pos());
            }
        });
        connect(m_menu, &DMenu::aboutToHide, this, [ = ] { dApp->m_app->restoreOverrideCursor(); });
        connect(m_menu, &DMenu::triggered, this, &ViewPanel::onMenuItemClicked);
        connect(dApp->setter, &ConfigSetter::valueChanged, this, [ = ] {
            if (this && this->isVisible())
            {
                updateMenuContent();
            }
        });
    }
}

void ViewPanel::appendAction(int id, const QString &text, const QString &shortcut)
{
    if (!dApp->isPanelDev() && m_menu) {
        QAction *ac = new QAction(m_menu);
        addAction(ac);
        ac->setText(text);
        ac->setProperty("MenuID", id);
        ac->setShortcut(QKeySequence(shortcut));
        m_menu->addAction(ac);
    }
}

void ViewPanel::onMenuItemClicked(QAction *action)
{
    using namespace utils::base;
    using namespace utils::image;

    //m_infos的count大于总和了，需要给总值重新赋值
    if (m_infos.count() > m_infosAll.count()) {
        m_infosAll = m_infos;
    }
    if (m_infos.isEmpty())
        return;
    const QString path = m_infos.at(m_current).filePath;
    const int id = action->property("MenuID").toInt();
    switch (MenuItemId(id)) {
    case IdFullScreen:
    case IdExitFullScreen:
        toggleFullScreen();
        break;
    case IdStartSlideShow: {
        //20201203旋转本地文件
        m_viewB->rotatePixCurrent();
        auto vinfo = m_vinfo;
        vinfo.fullScreen = window()->isFullScreen();
        vinfo.lastPanel = this;
        vinfo.path = path;
        //检测到只有一张图片的时候选择paths只赋1张
        if (m_infos.count() > 1) {
            vinfo.paths = slideshowpaths();
        } else {
            vinfo.paths = QStringList(path);
        }
        vinfo.viewMainWindowID = 0;

        //获取当前图片，节省第一张幻灯片加载图片的时间，在龙芯电脑上getFitImage耗时很严重，测试图片5.8M耗时0.6s
//        QPixmap pix = this->grab(QRect(QPoint( 0, 0 ),QSize( this->size().width(),this->size().height())));
//        QImage img = pix.toImage();
        if (m_viewB->getcurrentImgCount() > 1) {
            m_viewB->setCurrentImage(0);
        }
        QImage img = m_viewB->image();
        emit dApp->signalM->setFirstImg(img);
        emit dApp->signalM->startSlideShow(vinfo, m_vinfo.inDatabase);
        emit dApp->signalM->showSlidePanel(0);
        break;
    }
    case IdPrint: {
        //20201203旋转本地文件
        m_viewB->rotatePixCurrent();
        killTimer(m_hideCursorTid);
        m_hideCursorTid = 0;
        m_viewB->viewport()->setCursor(Qt::ArrowCursor);
        PrintHelper::getIntance()->showPrintDialog(QStringList(path), this);
        if (!m_menu->isVisible()) {
            m_viewB->viewport()->setCursor(Qt::BlankCursor);
        }
        m_hideCursorTid = startTimer(DELAY_HIDE_CURSOR_INTERVAL);
        break;
    }

    case IdRename: {
        //20201203旋转本地文件
        m_viewB->rotatePixCurrent();
        QString filepath = path;
        QString filename;
        if (PopRenameDialog(filepath, filename)) {
            m_rwLock.lockForWrite();
            //重命名后维护已经加载的文件名
            int allcurrent = 0;
            //增加判断，防止越界
            if (m_infosAll.count() > 1 && m_infos.count() > m_current) {
                allcurrent = m_infosAll.indexOf(m_infos[m_current]);
            }
            m_infos[m_current].fileName = filename;
            m_infos[m_current].filePath = filepath;
            if (m_infosAll.count() > 1) {
                m_infosAll[allcurrent].fileName = filename;
                m_infosAll[allcurrent].filePath = filepath;
            }
            m_rwLock.unlock();
            //修改链表里被修改文件的文件名
            connect(this, &ViewPanel::SetImglistPath, ttbc, &TTBContent::OnSetimglist);
            emit SetImglistPath(m_current, filename, filepath);
            //修改map维护的数据
            //dApp->getRwLock().lockForWrite();
            QMutexLocker locker(&dApp->getRwLock());
            dApp->m_imagemap.insert(filepath, dApp->m_imagemap[m_viewB->path()]);
            dApp->m_rectmap.insert(filepath, dApp->m_rectmap[m_viewB->path()]);
            dApp->m_imagemap.remove(path);
            // dApp->getRwLock().unlock();
            m_currentImagePath  = filepath;
            connect(this, &ViewPanel::changeitempath, ttbc, &TTBContent::OnChangeItemPath);
            emit changeitempath(m_current, filepath);
            //setPath改为setImage,2020/11/12 bug54269
            m_viewB->setImage(filepath);
        }
        break;
    }

    case IdCopy:
        copyImageToClipboard(QStringList(path));
        break;
    case IdMoveToTrash:
        //右键菜单删除action和delete快捷键删除图片
        if (m_dtr->isActive()) {
            return ;
        }
        m_dtr->start();
        if (!m_vinfo.inDatabase) {
            QFile file(path);
            if (!file.exists())
                break;
            //modify by heyi
            //先删除文件，需要判断文件是否删除，如果删除了，再决定看图软件的显示
            DDesktopServices::trash(path);
            QFile fileRemove(path);
            //文件是否被删除的判断bool值
            bool iRetRemove = false;
            if (!fileRemove.exists()) {
                iRetRemove = true;
            }
            //如果检测到文件已经被删除了，则选择在看图做对应的操作，否则不进行删除
            //因为smb和其他的情况受到了dtk的接口DDesktopServices::trash的控制，有时候会有弹出窗口
            if (iRetRemove) {
                if (removeCurrentImage()) {
                    emit dApp->signalM->picDelete();
                    ttbc->setIsConnectDel(true);
                    m_bAllowDel = true;
                    ttbc->disableDelAct(true);
                }
            }
        }
        break;

    case IdShowNavigationWindow:
        m_nav->setAlwaysHidden(false);
        break;
    case IdHideNavigationWindow:
        m_nav->setAlwaysHidden(true);
        break;
    case IdRotateClockwise:
        rotateImage(true);
        break;
    case IdRotateCounterclockwise:
        rotateImage(false);
        break;
    case IdSetAsWallpaper:
        if (m_viewB->getcurrentImgCount() > 1) {
            dApp->wpSetter->setWallpaper(m_viewB->image(false));
        } else {
            //20201208旋转本地文件 解决57329（旋转图片后设置壁纸，壁纸仍为旋转前状态）
            m_viewB->rotatePixCurrent();
            dApp->wpSetter->setWallpaper(path);
        }
        break;
    case IdDisplayInFileManager:
        emit dApp->signalM->showInFileManager(path);
        break;
    case IdImageInfo:
        if (m_isInfoShowed) {
            emit dApp->signalM->hideExtensionPanel();
        } else {
            emit dApp->signalM->showExtensionPanel();
            // Update panel info
            m_info->setImagePath(path);
        }
        break;
    case IdDraw: {
        QStringList pathlist;
        pathlist << path;
        emit dApp->signalM->sigDrawingBoard(pathlist);
        break;
    }
    case IdOcr: {
        m_viewB->slotsOcrCurrentPicture();
    }
    default:
        break;
    }

    updateMenuContent();
}

void ViewPanel::updateMenuContent()
{
    if (m_menu) {
        m_menu->clear();
        qDeleteAll(this->actions());

        if (m_infos.isEmpty()) {
            return;
        }

        if (window()->isFullScreen()) {
            appendAction(IdExitFullScreen, tr("Exit fullscreen"), ss("Fullscreen", "F11"));
        } else {
            appendAction(IdFullScreen, tr("Fullscreen"), ss("Fullscreen", "F11"));
        }

        appendAction(IdPrint, tr("Print"), ss("Print", "Ctrl+P"));
        //ocr按钮
        if (!m_isDynamicPic) {
            appendAction(IdOcr, tr("Extract text"), ss("Extract text", "Alt+O"));
        }
        //修复打开不支持显示的图片在缩略图中没有，current出现超出界限崩溃问题
        if (m_current >= m_infos.size()) m_current = 0;
        QFileInfo currfileinfo(m_infos.at(m_current).filePath);

        //判断图片数量大于0才能执行幻灯片播放
        if (m_infos.size() > 0) {
            appendAction(IdStartSlideShow, tr("Slide show"), ss("Slide show", "F5"));
        }

        m_menu->addSeparator();
        /**************************************************************************/
        appendAction(IdCopy, tr("Copy"), ss("Copy", "Ctrl+C"));
        if (currfileinfo.isReadable() &&
                currfileinfo.isWritable())
            appendAction(IdRename, tr("Rename"), ss("Rename", "F2"));
        //apple phone的delete没有权限,保险箱无法删除,垃圾箱也无法删除
        if ((currfileinfo.isReadable() && currfileinfo.isWritable()) && !dApp->IsApplePhone() && utils::image::isCanRemove(m_currentImagePath)) {
            appendAction(IdMoveToTrash, tr("Delete"), ss("Throw to trash", "Delete"));
        }

        m_menu->addSeparator();
        /**************************************************************************/
        if (!m_viewB->isWholeImageVisible() && m_nav->isAlwaysHidden() && GetPixmapStatus(m_currentImagePath)) {
            appendAction(IdShowNavigationWindow, tr("Show navigation window"),
                         ss("Show navigation window", ""));
        } else if (!m_viewB->isWholeImageVisible() && !m_nav->isAlwaysHidden() && GetPixmapStatus(m_currentImagePath)) {
            appendAction(IdHideNavigationWindow, tr("Hide navigation window"),
                         ss("Hide navigation window", ""));
        }
        /**************************************************************************/

        //apple手机特殊处理，不具备旋转功能
        if (m_stack->currentIndex() == 0 && currfileinfo.isReadable() &&
                currfileinfo.isWritable() &&
                utils::image::imageSupportSave(m_infos.at(m_current).filePath) &&
                !dApp->IsApplePhone()) {
            m_menu->addSeparator();
            appendAction(IdRotateClockwise, tr("Rotate clockwise"), ss("Rotate clockwise", "Ctrl+R"));
            appendAction(IdRotateCounterclockwise, tr("Rotate counterclockwise"),
                         ss("Rotate counterclockwise", "Ctrl+Shift+R"));
        }
        /**************************************************************************/
        if (m_stack->currentIndex() == 0 && utils::image::imageSupportWallPaper(m_infos.at(m_current).filePath)) {
            appendAction(IdSetAsWallpaper, tr("Set as wallpaper"), ss("Set as wallpaper", "Ctrl+F9"));
        }
        {
            appendAction(IdDisplayInFileManager, tr("Display in file manager"),
                         ss("Display in file manager", "Alt+D"));
        }
        appendAction(IdImageInfo, tr("Image info"), ss("Image info", "Ctrl+I"));
        //appendAction(IdDraw, tr("Draw"), ss("Draw", ""));
    }


}

void ViewPanel::clearMenu()
{
    if (m_menu) {
        m_menu->clear();
        qDeleteAll(this->actions());
    }
}

void ViewPanel::initShortcut()
{
    QShortcut *sc = nullptr;
    // Delay image toggle
    QTimer *m_dt = new QTimer(this);
    m_dt->setSingleShot(true);
    m_dt->setInterval(SWITCH_IMAGE_DELAY);

    // Previous
    sc = new QShortcut(QKeySequence(Qt::Key_Left), this);
    sc->setContext(Qt::WindowShortcut);
    connect(sc, &QShortcut::activated, this, [ = ] {
        if (!m_dt->isActive())
        {
            m_dt->start();
            showPrevious();
        }
    });
    // Next
    sc = new QShortcut(QKeySequence(Qt::Key_Right), this);
    sc->setContext(Qt::WindowShortcut);
    connect(sc, &QShortcut::activated, this, [ = ] {
        if (!m_dt->isActive())
        {
            m_dt->start();
            showNext();
        }
    });

    // Zoom out (Ctrl++ Not working, This is a confirmed bug in Qt 5.5.0)
    sc = new QShortcut(QKeySequence(Qt::Key_Up), this);
    sc->setContext(Qt::WindowShortcut);
    //fix 36530 当图片读取失败时（格式不支持、文件损坏、没有权限），不能进行缩放操作
    connect(sc, &QShortcut::activated, this, [ = ] {
        qDebug() << "Qt::Key_Up:";
        if (!m_viewB->image().isNull())
        {
            m_viewB->setScaleValue(1.1);
        }
    });
    sc = new QShortcut(QKeySequence("Ctrl++"), this);
    sc->setContext(Qt::WindowShortcut);
    connect(sc, &QShortcut::activated, this, [ = ] {
        if (QFile(m_viewB->path()).exists() && !m_viewB->image().isNull())
            m_viewB->setScaleValue(1.1);
    });
    sc = new QShortcut(QKeySequence("Ctrl+="), this);
    sc->setContext(Qt::WindowShortcut);
    connect(sc, &QShortcut::activated, this, [ = ] {
        if (QFile(m_viewB->path()).exists() && !m_viewB->image().isNull())
            m_viewB->setScaleValue(1.1);
    });
    // Zoom in
    sc = new QShortcut(QKeySequence(Qt::Key_Down), this);
    sc->setContext(Qt::WindowShortcut);
    connect(sc, &QShortcut::activated, this, [ = ] {
        qDebug() << "Qt::Key_Down:";
        if (QFile(m_viewB->path()).exists() && !m_viewB->image().isNull())
            m_viewB->setScaleValue(0.9);
    });
    sc = new QShortcut(QKeySequence("Ctrl+-"), this);
    sc->setContext(Qt::WindowShortcut);
    connect(sc, &QShortcut::activated, this, [ = ] {
        if (QFile(m_viewB->path()).exists() && !m_viewB->image().isNull())
            m_viewB->setScaleValue(0.9);
    });
    // Esc
//    QShortcut *esc = new QShortcut(QKeySequence(Qt::Key_Escape), this);
//    esc->setContext(Qt::WindowShortcut);
//    connect(esc, &QShortcut::activated, this, [ = ] {
//        if (window()->isFullScreen())
//        {
//            toggleFullScreen();
//        } else
//        {
//            if (m_vinfo.inDatabase) {
//                backToLastPanel();
//            } else {
//                dApp->quit();
//            }
//        }
//        emit dApp->signalM->hideExtensionPanel(true);
//    });
    // 1:1 size
    QShortcut *adaptImage = new QShortcut(QKeySequence("Ctrl+0"), this);
    adaptImage->setContext(Qt::WindowShortcut);
    connect(adaptImage, &QShortcut::activated, this, [ = ] {
        if (QFile(m_viewB->path()).exists())
            m_viewB->fitImage();
    });
}

