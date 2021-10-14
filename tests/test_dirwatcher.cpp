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
#include "gtestview.h"
#include "accessibility/ac-desktop-define.h"
#include "application.h"
#include "controller/signalmanager.h"
#define private public
#include "src/src/dirwatcher/scanpathsdialog.h"
#include "src/src/dirwatcher/scanpathsitem.h"
#include "src/src/dirwatcher/volumemonitor.h"

TEST_F(gtestview, cp2Image)
{
    for (int i = 0; i < 200; i++) {
        QFile::copy(":/jpg.jpg", QApplication::applicationDirPath() + "/test/jpg" + QString::number(i) + ".jpg");
        QFile(QApplication::applicationDirPath() + "/test/jpg" + QString::number(i) + ".jpg").setPermissions(\
                                                                                                             QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                                                             QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);
    }
}

//TEST_F(gtestview, ScanPathsDialog_show)
//{
//    ScanPathsDialog::instance()->show();
//    DBImgInfoList list;
//    DBImgInfo info;
//    info.format="png";
//    info.fileName=QApplication::applicationDirPath() + "/test/jpg188.jpg";
//    info.filePath=QApplication::applicationDirPath() + "/test/jpg100.jpg";
//    list.push_back(info);
//    dApp->signalM->imagesInserted(list);
//}
//TEST_F(gtestview, ScanPathsItem_1)
//{
//    ScanPathsItem *a=new ScanPathsItem(QApplication::applicationDirPath() + "/test/jpg101.jpg");
//    a->resize(200,200);
//    a->show();
//    QTest::keyClick(a, Qt::Key_Enter, Qt::ControlModifier, 50);
//    QTest::mouseMove(a, QPoint(20,20), 200);
//    a->hide();
//}
//VolumeMonitor

//TEST_F(gtestview, VolumeMonitor_1)
//{
//    VolumeMonitor::instance()->deviceAdded("");
//    VolumeMonitor::instance()->deviceRemoved("");
//    VolumeMonitor::instance()->isRunning();
//    VolumeMonitor::instance()->onFileChanged();
//    VolumeMonitor::instance()->stop();
//    VolumeMonitor::instance()->start();
//    VolumeMonitor::instance()->getMountPoint("x xx x x x x  ");
//    VolumeMonitor::instance()->getMountPoint("Test");
//}

//TEST_F(gtestview, ScanPathsDialog_1)
//{
//    QString path=QApplication::applicationDirPath() + "/test/jpg101.jpg";
//    ScanPathsDialog::instance()->isContainByScanPaths(path);
//    ScanPathsDialog::instance()->isSubPathOfScanPaths(path);
//    ScanPathsDialog::instance()->addToScanPaths(path);
//    ScanPathsDialog::instance()->removePath(path);
//    ScanPathsDialog::instance()->show();
//    ScanPathsDialog::instance()->hide();

//}



