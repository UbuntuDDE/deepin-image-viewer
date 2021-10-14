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
#include "src/src/module/modulepanel.h"
#include "src/src/widgets/imagebutton.h"
#include "src/src/module/view/navigationwidget.h"
#include "src/src/module/view/viewpanel.h"
#include <QPixmap>
#include <QImage>
#ifdef test_module_view_z
TEST_F(gtestview, moduleName)
{
    m_frameMainWindow = CommandLine::instance()->getMainWindow();

    ViewPanel *panel = m_frameMainWindow->findChild<ViewPanel *>(VIEW_PANEL_WIDGET);
    if (panel) {
        panel->moduleName();
        emit dApp->endThread();
        emit dApp->signalM->usbOutIn(true);
        emit dApp->signalM->usbOutIn(false);
        emit dApp->signalM->sigUpdateThunbnail(QApplication::applicationDirPath() + "/test/jpg40.jpg");
        emit dApp->signalM->UpdateNavImg();
    }
}


TEST_F(gtestview, RenameDialog)
{
    m_renameDialog = new RenameDialog(QApplication::applicationDirPath() + "/test/jpg52.jpg");
    m_renameDialog->show();
    m_renameDialog->GetFilePath();
    m_renameDialog->GetFileName();

    dApp->viewerTheme->setCurrentTheme(ViewerThemeManager::Dark);

    dApp->viewerTheme->setCurrentTheme(ViewerThemeManager::Light);

    dApp->viewerTheme->setCurrentTheme(ViewerThemeManager::Dark);


    m_renameDialog-> InitDlg();

    QTest::mouseMove(m_renameDialog->m_lineedt, QPoint(10, 10), 200);
    m_renameDialog->m_lineedt->setText("");
    QTest::keyClicks(m_renameDialog->m_lineedt, QString("jpg520.jpg"), Qt::NoModifier, 10);
    m_renameDialog->m_lineedt->setText("jpg520.jpg");

    QTest::mouseMove(m_renameDialog->okbtn, QPoint(), 200);
    QTest::mouseClick(m_renameDialog->okbtn, Qt::LeftButton, Qt::NoModifier, QPoint(), 200);

    m_renameDialog->okbtn->click();



    RenameDialog a("");
    a.show();
    a.m_lineedt->textEdited(QApplication::applicationDirPath() + "/test/jpg5200谢谢谢谢谢谢谢谢谢谢谢0.jpg" + QApplication::applicationDirPath() + "/test/jpg52000.jpg" + QApplication::applicationDirPath() + "/test/jpg52000.jpg");
    a.cancelbtn->click();

}

//NavigationWidget
TEST_F(gtestview, NavigationWidget_find)
{
    if (!m_frameMainWindow) {
        m_frameMainWindow = CommandLine::instance()->getMainWindow();
    }
    dApp->viewerTheme->setCurrentTheme(ViewerThemeManager::Dark);
    NavigationWidget *widget = m_frameMainWindow->findChild <NavigationWidget *>();
    if (widget) {
        widget->resize(200, 200);
        widget->show();
        widget->resize(300, 300);
        QImage a = QImage(QApplication::applicationDirPath() + "/png.png");

        widget->setImage(a);
        widget->resize(400, 400);
        QTest::mouseMove(widget, QPoint(10, 10), 150);
        QTest::mouseMove(widget, QPoint(10, 10), 100);
        widget->update();
        widget->hide();
        ImageButton *imgbutton = widget->findChild<ImageButton *>();
        imgbutton->clicked();

    }
}


#endif
