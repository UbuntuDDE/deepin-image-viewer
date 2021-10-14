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
//#include "scanpathsdialog.h"
//#include "scanpathsitem.h"
//#include "application.h"
//#include <ddialog.h>
//#include <dtitlebar.h>
//#include "controller/configsetter.h"
//#include "controller/dbmanager.h"
//#include "controller/signalmanager.h"
//#include "utils/baseutils.h"
//#include "widgets/imagebutton.h"
//#include <DFileDialog>
//#include <QFileSystemWatcher>
//#include <DPushButton>
//#include <QScreen>
//#include <QScrollArea>
//#include <QStandardPaths>
//#include <QVBoxLayout>
//#include <QDebug>

//DWIDGET_USE_NAMESPACE
//typedef DPushButton QPBtnDPushButton;
//typedef DFileDialog QFDToDFileDialog;

//namespace {

//const int DIALOG_WIDTH = 382;
//const int DIALOG_HEIGHT = 390;
//const int MESSAGE_DURATION = 2000;

//const QString SCANPATHS_GROUP = "SCANPATHSGROUP";
//const QString SCANPATHS_KEY = "SCANPATHSKEY";

//}  // namespace

//ScanPathsDialog::ScanPathsDialog(QWidget *parent)
//    : DMainWindow(parent)
//    ,m_messageTID(0)
//{
//    setWindowFlags(Qt::FramelessWindowHint);
//    setWindowModality(Qt::ApplicationModal);
//    if (titlebar()) titlebar()->setFixedHeight(0);
//    setFixedSize(DIALOG_WIDTH, DIALOG_HEIGHT);

//    QWdToDWidget *w = new QWdToDWidget(this);
//    setCentralWidget(w);
//    m_mainLayout = new QVBoxLayout(w);
//    m_mainLayout->setContentsMargins(0, 0, 0, 0);
//    m_mainLayout->setSpacing(0);

//    initTitle();
//    initPathsArea();
//    initMessageLabel();
//    initAddButton();
//    initSinglaFileWatcher();
//}

//ScanPathsDialog *ScanPathsDialog::m_dialog = NULL;
//ScanPathsDialog *ScanPathsDialog::instance()
//{
//    if (! m_dialog) {
//        m_dialog = new ScanPathsDialog();
//    }

//    return m_dialog;
//}

//void ScanPathsDialog::show()
//{
//    DMainWindow::show();

//    QRect gr;
//    QPoint pos = QCursor::pos();
//    for (QScreen *screen : qApp->screens()) {
//        if (screen->geometry().contains(pos)) {
//            gr = screen->geometry();
//            break;
//        }
//    }
//    QRect qr = geometry();
//    qr.moveCenter(gr.center());
//    move(qr.topLeft());

////    emit requestUpdateCount();
//}

//void ScanPathsDialog::timerEvent(QTimerEvent *e)
//{
//    if (e->timerId() == m_messageTID) {
//        m_messageLabel->setText("");
//        killTimer(m_messageTID);
//        m_messageTID = 0;
//    }
//    else {
//        DMainWindow::timerEvent(e);
//    }
//}

//void ScanPathsDialog::showSelectDialog()
//{
//    QFDToDFileDialog *dialog = new QFDToDFileDialog(this);
//    dialog->setWindowTitle(tr("Select Directory"));
//    dialog->setDirectory(QStandardPaths::standardLocations(
//                             QStandardPaths::PicturesLocation).first());
//    dialog->setAcceptMode(QFDToDFileDialog::AcceptOpen);
//    dialog->setFileMode(QFDToDFileDialog::Directory);
//    dialog->setOptions(
//                QFDToDFileDialog::ShowDirsOnly | QFDToDFileDialog::DontResolveSymlinks);
//    if (dialog->exec()) {
//        auto files = dialog->selectedFiles();
//        if (! files.isEmpty()) {
//            addPath(files.first());
//        }

//        dialog->deleteLater();
//    } else {
//        dialog->deleteLater();
//    }
//}

//bool ScanPathsDialog::addPath(const QString &path, bool check)
//{
//    if (check && (path.isEmpty() || ! isLegalPath(path))) {
//        // If path can't be select
//        showMessage(tr("This directory is disabled to sync"));
//        return false;
//    }
//    else if (check && isContainByScanPaths(path)) {
//        // If path is already in scan paths list
////        showMessage(tr("The path is already in scan paths list"));
//        return false;
//    }
//    else if (check && isSubPathOfScanPaths(path)) {
//        // If path is contain by others
////        showMessage(tr("The path is contain by scan paths list"));
//        return false;
//    }
//    else {
//        if (check) {
//            addToScanPaths(path);
//            m_contentStack->setCurrentIndex(1);
//        }

//        ScanPathsItem *item = new ScanPathsItem(path);
//        emit item->requestUpdateCount();
//        connect(this, &ScanPathsDialog::requestUpdateCount,
//                item, &ScanPathsItem::requestUpdateCount);
//        connect(item, &ScanPathsItem::remove, this, [=] (const QString &path) {
//            removePath(path);
//            m_pathsLayout->removeWidget(item);
//            item->deleteLater();
//        });
//        m_pathsLayout->addWidget(item);

//        return true;
//    }
//}

//void ScanPathsDialog::removePath(const QString &path)
//{
//    qDebug() << "Import Thread has been stopped, removing data from DB...";

//    // Remove from config-file
//    removeFromScanPaths(path);

//    // Remove data from DB
//    DBManager::instance()->removeDir(path);
//    if (scanpaths().isEmpty()) {
//        m_contentStack->setCurrentIndex(0);
//    }

//    qDebug() << "Data has been removed from DB.";
//}

//void ScanPathsDialog::initAddButton()
//{
//    QPBtnDPushButton * button = new QPBtnDPushButton(tr("Add folder"));
//    button->setFixedSize(310, 39);
//    button->setObjectName("AddButton");
//    m_mainLayout->addSpacing(7);
//    m_mainLayout->addWidget(button, 1, Qt::AlignCenter | Qt::AlignBottom);
//    m_mainLayout->addSpacing(27);

//    connect(button, SIGNAL(clicked(bool)), this, SLOT(showSelectDialog()));
//}

//void ScanPathsDialog::initSinglaFileWatcher()
//{
//    QFileSystemWatcher *wc = new QFileSystemWatcher();

//    QStringList rmPaths;
//    QStringList dirs;
//    QStringList dbPaths = DBManager::instance()->getPathsByDir(QString());
//    for (auto dbp : dbPaths) {
//        QFileInfo info(dbp);
//        if (! info.exists()) {
//            rmPaths << dbp;
//        }
//        else {
//            QString dir = info.path();
//            if (dirs.indexOf(dir) == -1) {
//                dirs << dir;
//            }
//        }
//    }

//    // Remove the images which is not exist
//    DBManager::instance()->removeImgInfos(rmPaths);

//    wc->addPaths(dirs);

//    connect(wc, &QFileSystemWatcher::directoryChanged,
//            this, [=] (const QString dir){
//        //修复style问题
//        m_rmPaths.clear();
//        for (auto dbp : DBManager::instance()->getPathsByDir(QString())) {
//            QFileInfo info(dbp);
//            if (info.path() == dir && ! info.exists()) {
//                m_rmPaths << dbp;
//            }
//        }
//        // Remove the images which is not exist
//        DBManager::instance()->removeImgInfos(m_rmPaths);
//    });
//    connect(dApp->signalM, &SignalManager::imagesInserted,
//            this, [=] (const DBImgInfoList &infos) {
//        for (auto info : infos) {
//            const QString emptyHash = utils::base::hash(QString());
//            if (info.dirHash == emptyHash) {
//                QFileInfo fi(info.filePath);
//                wc->addPath(fi.path());
//            }
//        }
//    });
//}

//void ScanPathsDialog::initTitle()
//{
//    QLbtoDLabel *title = new QLbtoDLabel(tr("Sync Directory Management"));
//    title->setAlignment(Qt::AlignCenter);
//    title->setObjectName("TitleLabel");

//    ImageButton* cb = new ImageButton(this);
//    cb->setObjectName("CloseButton");
//    cb->setTooltipVisible(true);
//    cb->setFixedSize(24, 24);
//    connect(cb, &ImageButton::clicked, this, &ScanPathsDialog::hide);

//    QWdToDWidget *w = new QWdToDWidget;
//    w->setFixedHeight(27);
//    QHBoxLayout *layout = new QHBoxLayout(w);
//    layout->setContentsMargins(24 + 5, 0, 5, 0);
//    layout->setSpacing(0);

//    layout->addWidget(title);
//    layout->addWidget(cb);
//    m_mainLayout->addSpacing(2);
//    m_mainLayout->addWidget(w);
//}

//void ScanPathsDialog::initPathsArea()
//{
//    // Empty frame
//    QLbtoDLabel *el = new QLbtoDLabel(tr("The directory list is empty"));
//    el->setAlignment(Qt::AlignCenter);
//    el->setObjectName("EmptyFrame");

//    // ScrollArea
//    QScrollArea *area = new QScrollArea;
//    area->setWidgetResizable(true);
//    area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    area->setObjectName("PathsScrollArea");

//    QWdToDWidget *areaContent = new QWdToDWidget;
//    areaContent->setObjectName("PathsContent");
//    m_pathsLayout = new QVBoxLayout(areaContent);
//    m_pathsLayout->setAlignment(Qt::AlignTop);
//    m_pathsLayout->setContentsMargins(0, 0, 0, 0);
//    m_pathsLayout->setSpacing(0);
//    area->setWidget(areaContent);

//    m_contentStack = new QSWToDStackedWidget;
//    m_contentStack->setContentsMargins(0, 0, 0, 0);
//    m_contentStack->setFixedSize(354, 250);
//    m_contentStack->addWidget(el);
//    m_contentStack->addWidget(area);
//    if (scanpaths().length() > 0) {
//        m_contentStack->setCurrentIndex(1);
//        auto paths = scanpaths();
//        for (auto p : paths) {
//            addPath(p, false);
//        }
//    }

//    m_mainLayout->addSpacing(14);
//    m_mainLayout->addWidget(m_contentStack, 1, Qt::AlignCenter);
//}

//void ScanPathsDialog::initMessageLabel()
//{
//    m_messageLabel = new QLbtoDLabel;
//    m_messageLabel->setObjectName("MessageLabel");
//    m_messageLabel->setAlignment(Qt::AlignCenter);
//    m_mainLayout->addSpacing(10);
//    m_mainLayout->addWidget(m_messageLabel);
//}

//void ScanPathsDialog::showMessage(const QString &message)
//{
//    killTimer(m_messageTID);
//    m_messageTID = startTimer(MESSAGE_DURATION);

//    m_messageLabel->setText(message);
//}

//bool ScanPathsDialog::isLegalPath(const QString &path) const
//{
//#ifdef Q_OS_LINUX
//    QStringList legalPrefixs;
//    legalPrefixs << QDir::homePath() + "/" << "/media/" << "/run/media/";
//    for (QString prefix : legalPrefixs) {
//        if (path.startsWith(prefix)) {
//            return true;
//        }
//    }
//    return false;
//#else
//    return true;
//#endif
//}

//bool ScanPathsDialog::isContainByScanPaths(const QString &path) const
//{
//    QStringList paths = scanpaths();
//    foreach (QString p , paths) {
//        if (p == path) {
//            return true;
//        }
//    }

//    return false;
//}

//bool ScanPathsDialog::isSubPathOfScanPaths(const QString &path) const
//{
//    auto paths = scanpaths();
//    foreach (QString p , paths) {
//        if (path.startsWith(p)) {
//            return true;
//        }
//    }

//    return false;
//}

//QStringList ScanPathsDialog::scanpaths() const
//{
//    QStringList paths = dApp->setter->value(SCANPATHS_GROUP, SCANPATHS_KEY)
//            .toString().split(",");
//    paths.removeAll("");
//    return paths;
//}

//void ScanPathsDialog::addToScanPaths(const QString &path)
//{
//    auto paths = scanpaths();
//    if (paths.contains(path))
//        return;
//    paths.append(path);
//    QString v;
//    for (QString p : paths) {
//        v += p + ",";
//    }
//    v.remove(v.length() - 1, 1);
//    dApp->setter->setValue(SCANPATHS_GROUP, SCANPATHS_KEY, v);
//}

//void ScanPathsDialog::removeFromScanPaths(const QString &path)
//{
//    auto paths = scanpaths();
//    paths.removeAll(path);
//    QString v;
//    foreach (QString p , paths) {
//        v += p + ",";
//    }
//    v.remove(v.length() - 1, 1);
//    dApp->setter->setValue(SCANPATHS_GROUP, SCANPATHS_KEY, v);
//}
