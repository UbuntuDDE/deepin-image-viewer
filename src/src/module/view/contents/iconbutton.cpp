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

#include "iconbutton.h"

#include <QDebug>
#include <QPainter>

#include <DHiDPIHelper>
#include <DPalette>

DGUI_USE_NAMESPACE

ImageIconButton::ImageIconButton(QWidget *parent)
    : DPushButton(parent)
{
}

ImageIconButton::ImageIconButton(const QString &normalPic, const QString &hoverPic,
                                 const QString &pressPic, const QString &checkedPic, QWidget *parent)
    : DPushButton(parent)
{
    defaultPicPath.normalPicPath = normalPic;
    defaultPicPath.hoverPicPath = hoverPic;
    defaultPicPath.pressPicPath = pressPic;
    defaultPicPath.checkedPicPath = checkedPic;

    auto pl = this->palette();
    QColor sbcolor("#000000");
    sbcolor.setAlphaF(0.05);
    pl.setColor(DPalette::Shadow, sbcolor);
    setPalette(pl);
}

//void ImageIconButton::setPropertyPic(QString propertyName, const QVariant &value,
//                                     const QString &normalPic, const QString &hoverPic, const QString &pressPic, const QString &checkedPic)
//{
//    ImagePicPathInfo curPicPath;
//    curPicPath.normalPicPath = normalPic;
//    curPicPath.hoverPicPath = hoverPic;
//    curPicPath.pressPicPath = pressPic;
//    curPicPath.checkedPicPath = checkedPic;

//    if (propertyPicPaths.first == propertyName) {
//        propertyPicPaths.second[value] = curPicPath;
//    } else {
//        QMap<QVariant, ImagePicPathInfo> curPicPathInfo;
//        curPicPathInfo.insert(value, curPicPath);
//        propertyPicPaths.first = propertyName;
//        propertyPicPaths.second = curPicPathInfo;
//    }
//}

//void ImageIconButton::setPropertyPic(const QString &normalPic, const QString &hoverPic, const QString &pressPic, const QString &checkedPic)
//{
//    defaultPicPath.normalPicPath = normalPic;
//    defaultPicPath.hoverPicPath = hoverPic;
//    defaultPicPath.pressPicPath = pressPic;
//    defaultPicPath.checkedPicPath = checkedPic;
//}

//void ImageIconButton::setTransparent(bool flag)
//{
//    transparent = flag;
//}

//void ImageIconButton::setAutoChecked(bool flag)
//{
//    autoChecked = flag;
//}

void ImageIconButton::paintEvent(QPaintEvent *event)
{
    if (!transparent) {
        DPushButton::paintEvent(event);
    }

    QString curPicPath = defaultPicPath.normalPicPath;
    if (propertyPicPaths.first.isEmpty() || !propertyPicPaths.second.contains(property(propertyPicPaths.first.toStdString().data()))) {
        QString curPropertyPicPathStr;
        if (isChecked() && !defaultPicPath.checkedPicPath.isEmpty()) {
            curPropertyPicPathStr = defaultPicPath.checkedPicPath;
        } else {
            if (status == 1 && !defaultPicPath.hoverPicPath.isEmpty()) {
                curPropertyPicPathStr = defaultPicPath.hoverPicPath;
            } else if (status == 2 && !defaultPicPath.pressPicPath.isEmpty()) {
                curPropertyPicPathStr = defaultPicPath.pressPicPath;
            }
        }

        if (!curPropertyPicPathStr.isEmpty()) {
            curPicPath = curPropertyPicPathStr;
        }
    } else {
        QVariant value = property(propertyPicPaths.first.toStdString().data());
        ImagePicPathInfo curPropertyPicPath = propertyPicPaths.second[value];
        QString curPropertyPicPathStr;
        if (isChecked() && !defaultPicPath.checkedPicPath.isEmpty()) {
            curPropertyPicPathStr = curPropertyPicPath.checkedPicPath;
        } else {
            if (status == 1 && !defaultPicPath.hoverPicPath.isEmpty()) {
                curPropertyPicPathStr = curPropertyPicPath.hoverPicPath;
            } else if (status == 2 && !defaultPicPath.pressPicPath.isEmpty()) {
                curPropertyPicPathStr = curPropertyPicPath.pressPicPath;
            } else {
                curPropertyPicPathStr = curPropertyPicPath.normalPicPath;
            }
        }
        if (!curPropertyPicPathStr.isEmpty()) {
            curPicPath = curPropertyPicPathStr;
        }
    }


    QIcon icon;
    icon.addFile(curPicPath);

    this->setIconSize(QSize(36, 36));
    this->setIcon(icon);

    DPushButton::paintEvent(event);
}

void ImageIconButton::enterEvent(QEvent *event)
{
    status = 1;
    DPushButton::enterEvent(event);
    if (autoChecked) {
        setChecked(true);
    }
}

void ImageIconButton::leaveEvent(QEvent *event)
{
    status = 0;
    DPushButton::leaveEvent(event);
    if (autoChecked) {
        setChecked(false);
    }
}

void ImageIconButton::mousePressEvent(QMouseEvent *event)
{
    status = 2;
    DPushButton::mousePressEvent(event);
}

void ImageIconButton::mouseReleaseEvent(QMouseEvent *event)
{
    status = 0;
    DPushButton::mouseReleaseEvent(event);
}
