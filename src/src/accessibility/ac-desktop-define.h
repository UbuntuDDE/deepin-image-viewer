/**
 * Copyright (C) 2020 UOS Technology Co., Ltd.
 *
 * to mark the desktop UI
 **/
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

#ifndef DESKTOP_ACCESSIBLE_UI_DEFINE_H
#define DESKTOP_ACCESSIBLE_UI_DEFINE_H

#include <QString>
#include <QObject>

//打开使用accessibility
#define ENABLE_ACCESSIBILITY

#ifdef ENABLE_ACCESSIBILITY
#define AC_SET_ACCESSIBLE_NAME(classObj,accessiblename) classObj->setAccessibleName(accessiblename);
#else
#define AC_SET_ACCESSIBLE_NAME(classObj,accessiblename)
#endif

#define AC_SET_OBJECT_NAME(classObj,objectname) classObj->setObjectName(objectname);

// 使用宏定义，方便国际化操作
#define INSTALLACCESSIBLEFACTORY
#define OPENACCESSIBLE

#define OPEN_IMAGE QObject::tr("Open Image") // 打开图片按钮
#define NOT_FOUND_IMAGE QObject::tr("Image file not found") // 图片未找到lab

#define Thumbnail_Label QObject::tr("ThumbnailLabel") // 缩略图lab
#define Thumbnail_Widget QObject::tr("ThumbnailWidget") // 缩略图widegt

#define Lock_Widget QObject::tr("LockWidget") // 现实不支持格式或损坏图片窗口

#define ADAPT_BUTTON QObject::tr("AdaptBtn")//１：１视图
#define PRE_BUTTON QObject::tr("PreviousButton")//上一张
#define NEXT_BUTTON QObject::tr("NextButton")//下一张
#define ADAPT_SCREEN_BUTTON QObject::tr("AdaptScreenBtn") //适应屏幕按钮
#define CLOCKWISE_ROTATION QObject::tr("Clockwise rotation") //顺时针旋转
#define COUNTER_CLOCKWISE_ROTATION QObject::tr("Counter clockwise rotation") //逆时针旋转
#define TRASH_BUTTON QObject::tr("trashbtn") //删除按钮
#define TTBCONTENT_WIDGET QObject::tr("ttbcontent") //缩略图区域

#define VIEW_PANEL_WIDGET QObject::tr("viewpanel") //图片显示区域
#define VIEW_PANEL_STACK QObject::tr("viewpanel stack") //图片显示区域堆栈窗口
#define IMAGE_LIST_WIDGET  QObject::tr("myimagelistwidget") //TTB中缩略图
#define IMAGE_VIEW QObject::tr("image view") //图片显示控件

#define PANEL_STACK QObject::tr("panelstack") //装有图片显示区域的视图窗口
#define MAIN_WIDGET QObject::tr("mainwidget") //主界面
#define MAIN_WIDOW QObject::tr("mainwindow") //主窗口
#define CENTER_WIDGET QObject::tr("centerwidget") //中心界面

#define SLIDE_SHOW_WIDGET QObject::tr("slide show widget") //幻灯片界面
#define SLIDE_SHOW_WIDGET_BUTTOM_BAR QObject::tr("slide show widget buttom bar") //幻灯片底部工具栏
#define SLIDE_SHOW_PRE_BUTTON QObject::tr("slide show previous button") //幻灯片底部工具栏上一张按钮
#define SLIDE_SHOW_NEXT_BUTTON QObject::tr("slide show next button") //幻灯片底部工具栏下一张按钮
#define SLIDE_SHOW_START_PAUSE_BUTTON QObject::tr("slide show start pause button") //幻灯片底部工具栏开始暂停按钮
#define SLIDE_SHOW_CANCEL_BUTTON QObject::tr("slide show cancel button") //幻灯片底部工具栏退出按钮
//新的幻灯片宏定义
#define Slider_Pre_Button QObject::tr("slide show previous button") //幻灯片底部工具栏上一张按钮
#define Slider_Next_Button QObject::tr("slide show next button") //幻灯片底部工具栏下一张按钮
#define Slider_Play_Pause_Button QObject::tr("slide show start pause button") //幻灯片底部工具栏开始暂停按钮
#define Slider_Exit_Button QObject::tr("slide show cancel button") //幻灯片底部工具栏退出按钮

#define TOP_TOOL_BAR QObject::tr("top tool bar") //顶部工具栏
#define TITLE_TEXT QObject::tr("title text") //顶部标题栏
#define TITLE_BAR QObject::tr("title bar") //顶部菜单
//#define SHADOW_LINE QObject::tr("shadow line") //阴影线

#define EXTENSION_PANEL QObject::tr("ExtensionPanel") //图片信息窗口
#define CONTENT_WIDGET QObject::tr("content widget") //图片信息界面
#define CONTENT_TITLE_BAR QObject::tr("title bar") //图片信息标题栏
#define CONTENT_SCROLL_AREA QObject::tr("scroll area") //图片信息滚动区域

#define BUTTOM_TOOL_BAR QObject::tr("buttom_tool_bar") //底部区域

#define IMAGE_WIDGET QObject::tr("imageinfo widget") //图片信息显示界面

#define RENAME_WIDGET QObject::tr("rename widget") //重命名界面
#define INPUT_EDIT QObject::tr("input edit") //重命名输入框
#define OK_BUTTON QObject::tr("Confirm") //重命名Ok按钮
#define CANCEL_BUTTON QObject::tr("Cancel") //重命名cancel按钮
#define RENAME_CONTENT QObject::tr("rename content") //重命名cancel按钮



#define SC_VIEW_SHORTCUT QObject::tr("sc_view_shortcut") //重命名cancel按钮
//其他
#define TOAST_OBJECT QObject::tr("toast")  //toast
#define THEME_WIDGET QObject::tr("theme widget")  //themewidget

#define NO_SCALE_RADIOBUTTON QObject::tr("No scaling")
#define FITTOIMAGE_RADIOBUTTON QObject::tr("Fit page to image")
#define FITTOPAGE_RADIOBUTTON QObject::tr("Fit image to page")
#define SCALE_RADIOBUTTON QObject::tr("Scale to")

#define TTL_CONTENTS QObject::tr("ttl content") //TTLContent

#define IMAGE_LIST_OBJECT QObject::tr("img list") //imglist

#define SLIDER_SHOW_MENU QObject::tr("slidershow_menu") //缩略图右键菜单

#define MOREPIC_UP_BUTTON QObject::tr("morepic_up_button") //多页图向上按键
#define MOREPIC_DOWN_BUTTON QObject::tr("morepic_down_button") //多页图向下按键

#endif // DESKTOP_ACCESSIBLE_UI_DEFINE_H
