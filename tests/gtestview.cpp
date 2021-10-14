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
#define  private public
#include <QKeySequence>
#include <QShortcut>
#include <QEnterEvent>
#include <QFile>
#include <QDir>

#include "accessibility/ac-desktop-define.h"
#include "widgets/toast.h"
#include "src/src/dirwatcher/scanpathsdialog.h"
#include "dirwatcher/volumemonitor.h"
#include "dirwatcher/scanpathsitem.h"
#include "module/view/scen/imageview.h"
#define protected public
#include "widgets/pushbutton.h"
#include "src/src/widgets/elidedlabel.h"

gtestview::gtestview()
{

}
TEST_F(gtestview, cpFile)
{
    QFile::copy(":/gif.gif", QApplication::applicationDirPath() + "/gif.gif");
    QFile(QApplication::applicationDirPath() + "/gif.gif").setPermissions(\
                                                                          QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                          QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/gif2.gif", QApplication::applicationDirPath() + "/gif2.gif");
    QFile(QApplication::applicationDirPath() + "/gif2.gif").setPermissions(\
                                                                           QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                           QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/ico.ico", QApplication::applicationDirPath() + "/ico.ico");
    QFile(QApplication::applicationDirPath() + "/ico.ico").setPermissions(\
                                                                          QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                          QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/jpg.jpg", QApplication::applicationDirPath() + "/jpg.jpg");
    QFile(QApplication::applicationDirPath() + "/jpg.jpg").setPermissions(\
                                                                          QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                          QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/mng.mng", QApplication::applicationDirPath() + "/mng.mng");
    QFile(QApplication::applicationDirPath() + "/mng.mng").setPermissions(\
                                                                          QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                          QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/png.png", QApplication::applicationDirPath() + "/png.png");
    QFile(QApplication::applicationDirPath() + "/png.png").setPermissions(\
                                                                          QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                          QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/svg.svg", QApplication::applicationDirPath() + "/svg.svg");
    QFile(QApplication::applicationDirPath() + "/svg.svg").setPermissions(\
                                                                          QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                          QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/svg1.svg", QApplication::applicationDirPath() + "/svg1.svg");
    QFile(QApplication::applicationDirPath() + "/svg1.svg").setPermissions(\
                                                                           QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                           QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/svg2.svg", QApplication::applicationDirPath() + "/svg2.svg");
    QFile(QApplication::applicationDirPath() + "/svg2.svg").setPermissions(\
                                                                           QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                           QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/svg1.svg", QApplication::applicationDirPath() + "/svg3.svg");
    QFile(QApplication::applicationDirPath() + "/svg3.svg").setPermissions(\
                                                                           QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                           QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/tif.tif", QApplication::applicationDirPath() + "/tif.tif");
    QFile(QApplication::applicationDirPath() + "/tif.tif").setPermissions(\
                                                                          QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                          QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/wbmp.wbmp", QApplication::applicationDirPath() + "/wbmp.wbmp");
    QFile(QApplication::applicationDirPath() + "/wbmp.wbmp").setPermissions(\
                                                                            QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                            QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/dds.dds", QApplication::applicationDirPath() + "/dds.dds");
    QFile(QApplication::applicationDirPath() + "/dds.dds").setPermissions(\
                                                                          QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                          QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/tga.tga", QApplication::applicationDirPath() + "/tga.tga");
    QFile(QApplication::applicationDirPath() + "/tga.tga").setPermissions(\
                                                                          QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                          QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QFile::copy(":/errorPic.icns", QApplication::applicationDirPath() + "/errorPic.icns");
    QFile(QApplication::applicationDirPath() + "/errorPic.icns").setPermissions(\
                                                                                QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                                QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);

    QDir a(QApplication::applicationDirPath());
    a.mkdir("test");
    QFile::copy(":/jpg.jpg", QApplication::applicationDirPath() + "/test/jpg.jpg");
    QFile(QApplication::applicationDirPath() + "/test/jpg.jpg").setPermissions(\
                                                                               QFile::WriteUser | QFile::ReadUser | QFile::WriteOther | \
                                                                               QFile::ReadOther | QFile::ReadGroup | QFile::WriteGroup);
}


//主窗体
TEST_F(gtestview, CommandLine)
{
    DApplicationSettings saveTheme;
    //4.将时间写入QDataStream
    QDateTime wstime = QDateTime::currentDateTime();
    QString teststr = wstime.toString("yyyy-MM-dd hh:mm:ss");
    bool newflag = true;
    CommandLine::instance()->processOption();
    QTest::qWait(500);
    CommandLine::instance()->processOption(wstime, newflag);
    QTest::qWait(500);

}
#ifdef test_main
TEST_F(gtestview, mainwindow)
{

    if (!m_frameMainWindow) {
        m_frameMainWindow = CommandLine::instance()->getMainWindow();
    }
    QTest::qWait(400);

    ViewPanel *panel = m_frameMainWindow->findChild<ViewPanel *>(VIEW_PANEL_WIDGET);
    if (panel) {
        // 打开保存绘制的 tif
        QString TriangleItemPath = QApplication::applicationDirPath() + "/tif.tif";
        TestApi::drogPathtoWidget(panel, TriangleItemPath);
    }

    m_frameMainWindow->setWindowRadius(18);
    m_frameMainWindow->setBorderWidth(0);
    m_frameMainWindow->show();
    QTest::mousePress(m_frameMainWindow, Qt::LeftButton);
    QTest::mouseRelease(m_frameMainWindow, Qt::LeftButton);
    QTest::mouseClick(m_frameMainWindow, Qt::LeftButton);
    QTest::mouseMove(m_frameMainWindow, QPoint(190, 50));
    QTest::mouseDClick(m_frameMainWindow, Qt::LeftButton);

    QTest::keyClick(m_frameMainWindow, Qt::Key_Down, Qt::ControlModifier, 200);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Down, Qt::ControlModifier, 200);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Down, Qt::ControlModifier, 200);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Down, Qt::ControlModifier, 200);

    QTest::keyClick(m_frameMainWindow, Qt::Key_Up, Qt::ControlModifier, 200);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Up, Qt::ControlModifier, 200);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Up, Qt::ControlModifier, 200);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Up, Qt::ControlModifier, 200);

    QTest::keyClick(m_frameMainWindow, Qt::Key_Right, Qt::NoModifier, 200);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Right, Qt::NoModifier, 200);
    int index1 = 0;
    while (index1++ < 20) {
        QTest::keyClick(m_frameMainWindow, Qt::Key_Left, Qt::NoModifier, 100);
    }
    while (index1-- > 0) {
        QTest::keyClick(m_frameMainWindow, Qt::Key_Right, Qt::NoModifier, 100);
    }
    QTest::keyClick(m_frameMainWindow, Qt::Key_Left, Qt::NoModifier, 200);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Up, Qt::ControlModifier, 100);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Up, Qt::ControlModifier, 100);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Up, Qt::ControlModifier, 100);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Down, Qt::ControlModifier, 100);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Down, Qt::ControlModifier, 100);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Down, Qt::ControlModifier, 100);

    QTest::keyClick(m_frameMainWindow, Qt::Key_F11, Qt::NoModifier, 1000);//
    QTest::mouseMove(m_frameMainWindow, QPoint(1000, 1075), 500);
    QTest::mouseMove(m_frameMainWindow, QPoint(200, 500), 500);
    int index = 0;
    while (index++ < 10)
        QTest::keyClick(m_frameMainWindow, Qt::Key_Plus, Qt::ControlModifier, 10);
    while (index-- > 0)
        QTest::keyClick(m_frameMainWindow, Qt::Key_Minus, Qt::ControlModifier, 10);
    QTest::mouseMove(m_frameMainWindow, QPoint(1000, 1075), 500);
    QTest::mouseMove(m_frameMainWindow, QPoint(200, 500), 500);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Escape, Qt::NoModifier, 500);

}

TEST_F(gtestview, sliderShow)
{
    if (!m_frameMainWindow) {
        m_frameMainWindow = CommandLine::instance()->getMainWindow();
    }
    QTest::qWait(100);
    m_frameMainWindow->showNormal();
    m_frameMainWindow->resize(800, 600);
    QTest::keyClick(m_frameMainWindow, Qt::Key_R, Qt::ControlModifier | Qt::ShiftModifier, 100);
    QTest::keyClick(m_frameMainWindow, Qt::Key_R, Qt::ControlModifier, 500);
    QTest::keyClick(m_frameMainWindow, Qt::Key_F5, Qt::NoModifier, 1000);
    QTest::qWait(90000);
    QTest::mouseMove(m_frameMainWindow, QPoint(1000, 1075), 1000);
    QTest::mouseMove(m_frameMainWindow, QPoint(200, 500), 1000);
    SlideShowPanel *sliderShow = m_frameMainWindow->findChild<SlideShowPanel *>(SLIDE_SHOW_WIDGET);

    m_frameMainWindow->customContextMenuRequested(QPoint(300, 300));
    QTest::mousePress(m_frameMainWindow, Qt::LeftButton, Qt::NoModifier, QPoint(100, 1020), 300);
    QTest::mouseRelease(m_frameMainWindow, Qt::LeftButton, Qt::NoModifier, QPoint(200, 1020), 300);
    QTest::mouseClick(m_frameMainWindow, Qt::LeftButton, Qt::NoModifier, QPoint(300, 1020), 300);
    QTest::mouseMove(m_frameMainWindow, QPoint(400, 1020), 300);
    QTest::mouseDClick(m_frameMainWindow, Qt::LeftButton, Qt::NoModifier, QPoint(500, 1020), 300);
    QTest::keyClick(m_frameMainWindow, Qt::Key_I, Qt::ControlModifier, 500);

    QTest::mouseClick(m_frameMainWindow, Qt::RightButton, Qt::NoModifier, QPoint(300, 1020), 300);

    QTest::mouseClick(m_frameMainWindow, Qt::MidButton, Qt::NoModifier, QPoint(300, 1020), 300);
    if (sliderShow) {
        sliderShow->customContextMenuRequested(QPoint(300, 300));
//        sliderShow->moduleName();
//        sliderShow->extensionPanelContent() ;
//        sliderShow->toolbarBottomContent() ;
//        sliderShow->toolbarTopMiddleContent() ;
//        sliderShow->toolbarTopLeftContent() ;

        DIconButton *buttonPre = dApp->findChild <DIconButton *>("PreviousButton");
        if (buttonPre) {
            buttonPre->click();

        }
        DIconButton *PlayPauseButton = dApp->findChild <DIconButton *>("PlayPauseButton");
        if (PlayPauseButton) {
            PlayPauseButton->click();
            QTest::qWait(100);
            PlayPauseButton->click();
        }

        DIconButton *nextButton = dApp->findChild <DIconButton *>("NextButton");
        if (nextButton) {
            nextButton->click();

        }

        DIconButton *CancelButton = dApp->findChild <DIconButton *>("CancelButton");
        if (CancelButton) {
            CancelButton->click();

        }
        QTest::mouseMove(sliderShow, QPoint(600, 500), 500);
        QTest::mouseMove(sliderShow, QPoint(800, 500), 500);
        QTest::mouseClick(sliderShow, Qt::LeftButton, Qt::NoModifier, QPoint(300, 600), 300);
        QTest::mouseDClick(sliderShow, Qt::LeftButton, Qt::NoModifier, QPoint(400, 600), 300);
        QMenu *menu = m_frameMainWindow->findChild<QMenu *>(SLIDER_SHOW_MENU);
        QAction *action1 =   m_frameMainWindow->findChild<QAction *> ("MenuID" + QString::number(SlideShowPanel::IdPlayOrPause))  ;
        if (action1) {
            qDebug() << "menu->triggered(action1);";
            menu->triggered(action1);
            QTest::qWait(300);
            menu->triggered(action1);
        }

    }

    QTest::keyClick(m_frameMainWindow, Qt::Key_Escape, Qt::NoModifier, 50);

    m_frameMainWindow->hide();
    m_frameMainWindow->showNormal();


}
TEST_F(gtestview, infoWidget)
{
    if (!m_frameMainWindow) {
        m_frameMainWindow = CommandLine::instance()->getMainWindow();
    }
    QTest::keyClick(m_frameMainWindow, Qt::Key_Escape, Qt::NoModifier, 100);
    m_frameMainWindow->resize(800, 600);
    QTest::keyClick(m_frameMainWindow, Qt::Key_I, Qt::ControlModifier, 100);

    QTest::keyClick(m_frameMainWindow, Qt::Key_Escape, Qt::NoModifier, 50);
}

TEST_F(gtestview, iconRotatePic)
{
    if (!m_frameMainWindow) {
        m_frameMainWindow = CommandLine::instance()->getMainWindow();
    }
    DIconButton *m_adaptImageBtn = m_frameMainWindow->findChild<DIconButton *>(ADAPT_BUTTON);
    DIconButton *m_adaptScreenBtn = m_frameMainWindow->findChild<DIconButton *>(ADAPT_SCREEN_BUTTON);
    DIconButton *m_preButton = m_frameMainWindow->findChild<DIconButton *>(PRE_BUTTON);
    DIconButton *m_nextButton = m_frameMainWindow->findChild<DIconButton *>(NEXT_BUTTON);
    DIconButton *m_rotateRBtn = m_frameMainWindow->findChild<DIconButton *>(CLOCKWISE_ROTATION);
    DIconButton *m_rotateLBtn = m_frameMainWindow->findChild<DIconButton *>(COUNTER_CLOCKWISE_ROTATION);
    DIconButton *m_trashBtn = m_frameMainWindow->findChild<DIconButton *>(TRASH_BUTTON);
    ViewPanel *panel = m_frameMainWindow->findChild<ViewPanel *>(VIEW_PANEL_WIDGET);
    if (panel) {
        m_adaptImageBtn->click();
        QTest::qWait(100);
        m_adaptScreenBtn->click();
        QTest::qWait(100);
        m_preButton->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_rotateRBtn->click();
        QTest::qWait(100);
        m_rotateLBtn->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_adaptScreenBtn->click();
        QTest::qWait(100);
        m_preButton->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_rotateRBtn->click();
        QTest::qWait(100);
        m_rotateLBtn->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_adaptScreenBtn->click();
        QTest::qWait(100);
        m_preButton->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_rotateRBtn->click();
        QTest::qWait(100);
        m_rotateLBtn->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_adaptScreenBtn->click();
        QTest::qWait(100);
        m_preButton->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_rotateRBtn->click();
        QTest::qWait(100);
        m_rotateLBtn->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_adaptScreenBtn->click();
        QTest::qWait(100);
        m_preButton->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_rotateRBtn->click();
        QTest::qWait(100);
        m_rotateLBtn->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_adaptScreenBtn->click();
        QTest::qWait(100);
        m_preButton->click();
        QTest::qWait(100);
        m_nextButton->click();
        QTest::qWait(100);
        m_rotateRBtn->click();
        QTest::qWait(100);
        m_rotateLBtn->click();
        QTest::qWait(1000);
        m_nextButton->click();
        QTest::qWait(100);



    }

}

TEST_F(gtestview, onlyonePic)
{
    if (!m_frameMainWindow) {
        m_frameMainWindow = CommandLine::instance()->getMainWindow();
    }
    QTest::qWait(200);
    //    SLIDE_SHOW_WIDGET
    ViewPanel *panel = m_frameMainWindow->findChild<ViewPanel *>(VIEW_PANEL_WIDGET);
    if (panel) {
        // 打开 jpg
        QString TriangleItemPath = QApplication::applicationDirPath() + "/test/jpg.jpg";
        TestApi::drogPathtoWidget(panel, TriangleItemPath);
        QTest::qWait(2000);

        DIconButton *m_adaptImageBtn = m_frameMainWindow->findChild<DIconButton *>(ADAPT_BUTTON);
        DIconButton *m_adaptScreenBtn = m_frameMainWindow->findChild<DIconButton *>(ADAPT_SCREEN_BUTTON);
        DIconButton *m_rotateRBtn = m_frameMainWindow->findChild<DIconButton *>(CLOCKWISE_ROTATION);
        DIconButton *m_rotateLBtn = m_frameMainWindow->findChild<DIconButton *>(COUNTER_CLOCKWISE_ROTATION);
        DIconButton *m_trashBtn = m_frameMainWindow->findChild<DIconButton *>(TRASH_BUTTON);

        m_adaptImageBtn->click();
        QTest::qWait(100);
        m_adaptScreenBtn->click();
        QTest::qWait(100);
        m_rotateRBtn->click();
        QTest::qWait(100);
        m_rotateLBtn->click();
        QTest::qWait(100);

        int index = 0;
        while (index++ < 10)
            QTest::keyClick(m_frameMainWindow, Qt::Key_Plus, Qt::ControlModifier, 20);
        while (index-- > 0)
            QTest::keyClick(m_frameMainWindow, Qt::Key_Minus, Qt::ControlModifier, 20);

        m_frameMainWindow->showFullScreen();
        QTest::keyClick(m_frameMainWindow, Qt::Key_Escape, Qt::NoModifier, 200);
        m_frameMainWindow->showNormal();

        QTest::keyClick(m_frameMainWindow, Qt::Key_F5, Qt::NoModifier, 200);
        QTest::keyClick(m_frameMainWindow, Qt::Key_Escape, Qt::NoModifier, 200);
        m_frameMainWindow->showNormal();

        m_trashBtn->click();
        QTest::qWait(50);
    }
}

TEST_F(gtestview, sliderSvg)
{
    if (!m_frameMainWindow) {
        m_frameMainWindow = CommandLine::instance()->getMainWindow();
    }
    //    SLIDE_SHOW_WIDGET
    ViewPanel *panel = m_frameMainWindow->findChild<ViewPanel *>(VIEW_PANEL_WIDGET);
    if (panel) {
        // 打开 svg
        QString TriangleItemPath = QApplication::applicationDirPath() + "/svg.svg";
        TestApi::drogPathtoWidget(panel, TriangleItemPath);
    }
    QTest::keyClick(m_frameMainWindow, Qt::Key_F5, Qt::NoModifier, 100);
    QTest::keyClick(m_frameMainWindow, Qt::Key_Escape, Qt::NoModifier, 200);
    m_frameMainWindow->hide();
    m_frameMainWindow->showMaximized();
    m_frameMainWindow->showNormal();
}

TEST_F(gtestview, MyImageListWidget)
{
    if (!m_frameMainWindow) {
        m_frameMainWindow = CommandLine::instance()->getMainWindow();
    }
    MyImageListWidget *widget = m_frameMainWindow->findChild<MyImageListWidget *>(IMAGE_LIST_WIDGET);
    ASSERT_NE(widget, nullptr);

    QTestEventList e;
    e.addMouseMove(QPoint(100, 30), 200);
    e.addMousePress(Qt::LeftButton, Qt::NoModifier, QPoint(100, 30), 200);
    e.addMouseMove(QPoint(150, 30), 200);
    e.addMouseMove(QPoint(200, 30), 200);
    e.addMouseRelease(Qt::LeftButton, Qt::NoModifier, QPoint(250, 30), 200);
    e.simulate(widget);
    e.clear();
}

//设置背景颜色
TEST_F(gtestview, ViewerThemeManager)
{
    dApp->viewerTheme->setCurrentTheme(ViewerThemeManager::Dark);
    dApp->viewerTheme->setCurrentTheme(ViewerThemeManager::Light);
}

TEST_F(gtestview, ImageButton)
{
    ImageButton *button = new ImageButton();
    QEnterEvent *event = new QEnterEvent(QPointF(200, 200), QPointF(200, 200), QPointF(200, 200));
    button->enterEvent(event);
    button->leaveEvent(event);
    delete event;
    event = nullptr;

    button->showTooltip(QPoint(200, 200));
    button->setDisabled(false);
    button->setToolTip("test");
    button->getDisablePic();
    button->show();
    button->resize(100, 100);

    QTest::qWait(100);
    QTest::mousePress(button, Qt::LeftButton, Qt::NoModifier, QPoint(50, 50), 250);
    QTest::qWait(100);
    QTest::mouseRelease(button, Qt::LeftButton);
    QTest::mouseClick(button, Qt::LeftButton);
    QTest::mouseMove(button, QPoint(20, 20), 250);
    QTest::keyClick(button, Qt::Key_Escape, Qt::ShiftModifier, 1000);
    QTest::mouseDClick(button, Qt::LeftButton, Qt::NoModifier, QPoint(50, 50), 200);

    button->hide();
    button->showTooltip(QPoint(200, 200));
    button->deleteLater();
    button = nullptr;
}

TEST_F(gtestview, m_pushbutton)
{
    m_pushbutton = new PushButton();

    m_pushbutton->m_checkedPic = ":/common/images/dialog_warning.svg";
    m_pushbutton->m_currentPic = ":/common/images/dialog_warning.svg";
    m_pushbutton->m_disablePic = ":/common/images/dialog_warning.svg";
    m_pushbutton->m_checked = false;
    m_pushbutton->setVisible(true);
    m_pushbutton->getPixmap();
    m_pushbutton->setVisible(false);
    m_pushbutton->getPixmap();
    m_pushbutton->m_checked = true;
    m_pushbutton->getPixmap();
    QEnterEvent *event = new QEnterEvent(QPointF(200, 200), QPointF(200, 200), QPointF(200, 200));
    m_pushbutton->enterEvent(event);
    m_pushbutton->leaveEvent(event);
    delete event;
    event = nullptr;

    m_pushbutton->showTooltip(QPoint(200, 200));
    m_pushbutton->normalPic();
    m_pushbutton-> hoverPic() ;
    m_pushbutton-> pressPic() ;
    m_pushbutton-> disablePic() ;
    m_pushbutton-> checkedPic() ;
    m_pushbutton-> text() ;
    m_pushbutton-> normalColor() ;
    m_pushbutton-> hoverColor() ;
    m_pushbutton-> pressColor() ;
    m_pushbutton-> disableColor() ;
    m_pushbutton-> setToolTip("TEST");
    m_pushbutton-> setChecked(false);
    m_pushbutton-> setText("test");
    m_pushbutton-> setToolTip("TEST");
    m_pushbutton-> setChecked(true);
    m_pushbutton-> setText("test");
    m_pushbutton->show();

    QTest::mousePress(m_pushbutton, Qt::LeftButton, Qt::NoModifier, QPoint(20, 20), 500);
    QTest::mouseRelease(m_pushbutton, Qt::LeftButton, Qt::NoModifier, QPoint(20, 20), 500);
    QTest::mouseClick(m_pushbutton, Qt::LeftButton, Qt::NoModifier, QPoint(20, 20), 500);
    QTest::mouseMove(m_pushbutton, QPoint(20, 20), 500);
    QTest::keyClick(m_pushbutton, Qt::Key_Escape, Qt::ShiftModifier, 1000);
    QTest::mouseDClick(m_pushbutton, Qt::LeftButton);

    m_pushbutton->hide();
}

TEST_F(gtestview, LockWidget)
{
    m_lockWidget = new LockWidget("", "");
    m_lockWidget->show();

    QTest::mousePress(m_lockWidget, Qt::LeftButton, Qt::NoModifier, QPoint(20, 20), 200);
    QTest::mouseRelease(m_lockWidget, Qt::LeftButton);
    QTest::mouseClick(m_lockWidget, Qt::LeftButton);
    QTest::mouseMove(m_lockWidget, QPoint(20, 20), 200);
    QTest::keyClick(m_lockWidget, Qt::Key_Escape, Qt::ShiftModifier, 200);
    QTest::mouseDClick(m_lockWidget, Qt::LeftButton);

    m_lockWidget->hide();
}
TEST_F(gtestview, ThumbnailWidget)
{
    m_thumbnailWidget = new ThumbnailWidget(m_SVGPath, m_SVGPath);
    m_thumbnailWidget->show();

    QTest::mousePress(m_thumbnailWidget, Qt::LeftButton, Qt::NoModifier, QPoint(20, 20), 200);
    QTest::mouseRelease(m_thumbnailWidget, Qt::LeftButton);
    QTest::mouseClick(m_thumbnailWidget, Qt::LeftButton);
    QTest::mouseMove(m_thumbnailWidget, QPoint(20, 20), 200);
    QTest::keyClick(m_thumbnailWidget, Qt::Key_Escape, Qt::ShiftModifier, 200);
    QTest::mouseDClick(m_thumbnailWidget, Qt::LeftButton);

    m_thumbnailWidget->hide();
}
TEST_F(gtestview, NavigationWidget)
{
    m_navigationWidget = new NavigationWidget();
    m_navigationWidget->show();

    QTest::mousePress(m_navigationWidget, Qt::LeftButton, Qt::NoModifier, QPoint(20, 20), 200);
    QTest::mouseRelease(m_navigationWidget, Qt::LeftButton);
    QTest::mouseClick(m_navigationWidget, Qt::LeftButton);
    QTest::mouseMove(m_navigationWidget, QPoint(20, 20), 200);
    QTest::keyClick(m_navigationWidget, Qt::Key_Escape, Qt::ShiftModifier, 200);
    QTest::mouseDClick(m_navigationWidget, Qt::LeftButton);

    m_navigationWidget->hide();
}
TEST_F(gtestview, ImageIconButton)
{
    m_ImageIconButton1 = new ImageIconButton();
    m_ImageIconButton1->show();
    m_ImageIconButton1->resize(50, 50);

    QTest::mousePress(m_ImageIconButton1, Qt::LeftButton, Qt::NoModifier, QPoint(20, 20), 500);
    QTest::mouseRelease(m_ImageIconButton1, Qt::LeftButton);
    QTest::mouseClick(m_ImageIconButton1, Qt::LeftButton);
    QTest::mouseMove(m_ImageIconButton1, QPoint(20, 20), 500);
    QTest::keyClick(m_ImageIconButton1, Qt::Key_Escape, Qt::ShiftModifier, 1000);
    QTest::mouseDClick(m_ImageIconButton1, Qt::LeftButton);

    m_ImageIconButton1->update();
    m_ImageIconButton1->update();
    m_ImageIconButton2 = new ImageIconButton(m_SVGPath, m_SVGPath, m_SVGPath, m_SVGPath);
    m_ImageIconButton2->show();
    m_ImageIconButton2->resize(50, 50);

    QTest::mousePress(m_ImageIconButton2, Qt::LeftButton, Qt::NoModifier, QPoint(20, 20), 200);
    QTest::mouseRelease(m_ImageIconButton2, Qt::LeftButton, Qt::NoModifier, QPoint(20, 20), 200);
    QTest::mouseClick(m_ImageIconButton2, Qt::LeftButton, Qt::NoModifier, QPoint(30, 30), 200);
    QTest::mouseMove(m_ImageIconButton2, QPoint(20, 45), 200);
    QTest::keyClick(m_ImageIconButton2, Qt::Key_Escape, Qt::ShiftModifier, 200);
    QTest::mouseDClick(m_ImageIconButton2, Qt::LeftButton, Qt::NoModifier, QPoint(20, 30), 200);

    QEnterEvent *event = new QEnterEvent(QPointF(200, 200), QPointF(200, 200), QPointF(200, 200));
    m_ImageIconButton1->enterEvent(event);
    m_ImageIconButton1->leaveEvent(event);
    delete event;
    event = nullptr;

    m_ImageIconButton1->hide();
    m_ImageIconButton2->hide();
    m_ImageIconButton1->deleteLater();
    m_ImageIconButton1 = nullptr;


}
TEST_F(gtestview, ImageInfoWidget)
{
    m_ImageInfoWidget = new ImageInfoWidget("", "");
    m_ImageInfoWidget->setImagePath(m_JPGPath);
    m_ImageInfoWidget->contentHeight();
    m_ImageInfoWidget->hide();
}
TEST_F(gtestview, ImageView)
{
    m_ImageView = new ImageView();
    m_ImageView->setImage(m_JPGPath);
    m_ImageView->resize(500, 500);
    m_ImageView->show();
    m_ImageView->cachePixmap(m_JPGPath);
    m_ImageView->fitWindow();
    m_ImageView->fitWindow_btnclicked();
    m_ImageView->fitImage();
    m_ImageView->rotateClockWise();
    m_ImageView->rotateCounterclockwise();

    m_ImageView->autoFit();
    m_ImageView->titleBarControl();
    m_ImageView->image();
    m_ImageView->windowRelativeScale();
    m_ImageView->windowRelativeScale_origin();
    m_ImageView->imageRect();
    m_ImageView->path();

    m_ImageView->visibleImageRect();
    m_ImageView->isWholeImageVisible();
    m_ImageView->isFitImage();
    m_ImageView->isFitWindow();
    m_ImageView->rotatePixCurrent();

    emit m_ImageView->clicked();
    emit m_ImageView->doubleClicked();
    emit m_ImageView->mouseHoverMoved();
    emit m_ImageView->scaled(200);
    emit m_ImageView->transformChanged();
    emit m_ImageView->showScaleLabel();
    emit m_ImageView->nextRequested();
    emit m_ImageView->previousRequested();
    emit m_ImageView->disCheckAdaptImageBtn();
    emit m_ImageView->checkAdaptImageBtn();
    emit m_ImageView->clicked();
    m_ImageView->mapToImage(QPoint());
    m_ImageView->mapToImage(QRect());
    m_ImageView->centerOn(5, 5);
    m_ImageView->setRenderer();
    m_ImageView->setScaleValue(qreal());
    QTest::mousePress(m_ImageView->viewport(), Qt::LeftButton, Qt::NoModifier, QPoint(50, 50), 200);
    QTest::mouseRelease(m_ImageView->viewport(), Qt::LeftButton, Qt::NoModifier, QPoint(100, 100), 200);
    QTest::mouseClick(m_ImageView->viewport(), Qt::LeftButton, Qt::NoModifier, QPoint(50, 50), 200);
    QTest::mouseMove(m_ImageView->viewport(), QPoint(50, 100), 200);
    QTest::keyClick(m_ImageView->viewport(), Qt::Key_Escape, Qt::ShiftModifier, 200);
    QTest::mouseDClick(m_ImageView->viewport(), Qt::LeftButton, Qt::NoModifier, QPoint(50, 50), 200);
    // 打开保存绘制的 tif
    QString TriangleItemPath = QApplication::applicationDirPath() + "/tif.tif";
    TestApi::drogPathtoWidget(m_ImageView->viewport(), TriangleItemPath);

    m_ImageView->hide();
}

TEST_F(gtestview, dapp)
{
    dApp->getRwLock();
    dApp->loadInterface(m_JPGPath);
    dApp->signalM->emit sendPathlist(list, m_JPGPath);
}

TEST_F(gtestview, unionimage)
{
    //unionimage
    QString pppath = m_PNGPath;

    QImage rimg(pppath);
    QImage img2;
    QString errorMsg;
    QSize realSize;
    loadStaticImageFromFile(m_DDSPath, img2, realSize, errorMsg);
    detectImageFormat(m_DDSPath);
    rotateImage(90, img2);
    QString ddsPath = m_DDSPath;
    QString svgPath = m_SVGPath;
    rotateImageFIle(90, m_SVGPath, errorMsg);
    rotateImageFIle(90, pppath, errorMsg);
    DetectImageFormat(m_SVGPath);
}
TEST_F(gtestview, imageutil)
{
    qDebug() << "imageutil1";
    showInFileManager("");
    qDebug() << "imageutil22";
    copyImageToClipboard(list);
    trashFile(m_JPGPath);

    SpliteText("/usr/share/wallpapers/deepin/Hummingbird_by_Shu_Le.jpg/usr/share/wallpapers/deepin/Hummingbird_by_Shu_Le.jpg/usr/share/wallpapers/deepin/Hummingbird_by_Shu_Le.jpg", QFont(), 20, false);
    SpliteText("/usr/share/wallpapers/deepin/Hummingbird_by_Shu_Le.jpg/usr/share/wallpapers/deepin/Hummingbird_by_Shu_Le.jpg/usr/share/wallpapers/deepin/Hummingbird_by_Shu_Le.jpg", QFont(), 20, true);

    QString ppath = m_JPGPath;
    onMountDevice(ppath);
    mountDeviceExist(ppath);

    //utils::image
    QString pppath = m_JPGPath;
    rotate(pppath, 90);
    cutSquareImage(QPixmap(pppath), QSize(50, 50));
    utils::image::getOrientation(pppath);
    bool iRet = false;

    getRotatedImage(pppath);
    cachePixmap(pppath);
    getThumbnail(pppath, iRet);
    supportedImageFormats();
    imageSupportWallPaper(pppath);
    utils::image::suffixisImage(pppath);

}

TEST_F(gtestview, ExtensionPanel)
{
    m_extensionPanel = new ExtensionPanel(nullptr);
    m_extensionPanel->show();
    m_extensionPanel->setContent(new QWidget());
    m_extensionPanel->setContent(nullptr);
    m_extensionPanel->resize(200, 200);
    QTest::mousePress(m_extensionPanel, Qt::LeftButton, Qt::NoModifier, QPoint(50, 50), 100);
    QTest::mouseRelease(m_extensionPanel, Qt::LeftButton, Qt::NoModifier, QPoint(100, 100), 100);
    QTest::mouseClick(m_extensionPanel, Qt::LeftButton, Qt::NoModifier, QPoint(50, 50), 100);
    QTest::mouseMove(m_extensionPanel, QPoint(20, 20), 100);
    QTest::keyClick(m_extensionPanel, Qt::Key_Escape, Qt::ShiftModifier, 100);
    QTest::mouseDClick(m_extensionPanel, Qt::LeftButton, Qt::NoModifier, QPoint(50, 50), 100);
    m_extensionPanel->setContent(new QWidget());
    m_extensionPanel->setContent(nullptr);
    QTest::mousePress(m_extensionPanel, Qt::LeftButton, Qt::NoModifier, QPoint(20, 50), 100);
    QTest::mouseRelease(m_extensionPanel, Qt::LeftButton, Qt::NoModifier, QPoint(50, 50), 100);
    QTest::mouseClick(m_extensionPanel, Qt::LeftButton, Qt::NoModifier, QPoint(50, 50), 100);
    QTest::mouseMove(m_extensionPanel, QPoint(50, 50), 50);
    QTest::mouseDClick(m_extensionPanel, Qt::LeftButton);

    m_extensionPanel->close();
    if (m_extensionPanel) {
        m_extensionPanel->deleteLater();
        m_extensionPanel = nullptr;
    }
}
TEST_F(gtestview, Toast)
{
    if (!m_frameMainWindow) {
        m_frameMainWindow = CommandLine::instance()->getMainWindow();
    }

    Toast *widget = m_frameMainWindow->findChild<Toast *>(TOAST_OBJECT);
    if (widget) {
        widget->icon();
        widget->setText("toast");
        widget->text();
        widget->setOpacity(qreal(5));
        widget->opacity();
    } else {
        widget = new Toast();
        widget->icon();
        widget->setText("toast");
        widget->text();
        widget->setOpacity(qreal(5));
        widget->opacity();
        widget->deleteLater();
        widget = nullptr;
    }

}

TEST_F(gtestview, ThemeWidget)
{
    if (!m_frameMainWindow) {
        m_frameMainWindow = CommandLine::instance()->getMainWindow();
    }

    ThemeWidget *widget = m_frameMainWindow->findChild<ThemeWidget *>(THEME_WIDGET);
    if (!widget) {
        widget = new ThemeWidget("", "");
        widget->deleteLater();
        widget = nullptr;
    }
}

TEST_F(gtestview, Dark)
{
    dApp->viewerTheme->setCurrentTheme(ViewerThemeManager::Dark);
}

TEST_F(gtestview, Light)
{
    dApp->viewerTheme->setCurrentTheme(ViewerThemeManager::Light);
}

TEST_F(gtestview, ElidedLabel)
{
    if (CommandLine::instance()->getMainWindow()) {
        QWidget *widget = new QWidget();
        ElidedLabel *elide = new ElidedLabel(widget);
        elide->setText("test");
        elide->show();
        elide->resize(50, 50);
        elide->update();
        QTest::qWait(50);
        dApp->viewerTheme->setCurrentTheme(ViewerThemeManager::Dark);
        QTest::qWait(50);
        dApp->viewerTheme->setCurrentTheme(ViewerThemeManager::Light);
        QTest::qWait(50);
        elide->onThemeChanged(ViewerThemeManager::Dark);
        elide->onThemeChanged(ViewerThemeManager::Light);
        QPaintEvent *paint = new QPaintEvent(QRect(200, 200, 200, 200));
        elide->paintEvent(paint);
        delete paint;
        paint = nullptr;
        elide->deleteLater();
        elide = nullptr;
        widget->deleteLater();
        widget = nullptr;
    }
}

#endif
