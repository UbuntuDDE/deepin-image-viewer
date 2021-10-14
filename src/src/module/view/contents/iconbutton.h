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

#ifndef IMAGEICONBUTTON_H
#define IMAGEICONBUTTON_H
#pragma once

#include <QScopedPointer>
#include <QMap>
#include <QVariant>

#include <DPushButton>

DWIDGET_USE_NAMESPACE

class ImageIconButton : public DPushButton
{
    struct ImagePicPathInfo {
        QString normalPicPath;
        QString hoverPicPath;
        QString pressPicPath;
        QString checkedPicPath;
    };

    Q_OBJECT
public:
    explicit ImageIconButton(QWidget *parent = Q_NULLPTR);

    ImageIconButton(const QString &normalPic, const QString &hoverPic,
                    const QString &pressPic, const QString &checkedPic = QString(), QWidget *parent = 0);

//    void setPropertyPic(QString propertyName, const QVariant &value, const QString &normalPic, const QString &hoverPic,
//                        const QString &pressPic, const QString &checkedPic = QString());
//    void setPropertyPic(const QString &normalPic, const QString &hoverPic,
//                        const QString &pressPic, const QString &checkedPic = QString());

//    void setTransparent(bool flag);
//    void setAutoChecked(bool flag);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    char                                               status                  = 0;
    bool                                               autoChecked             = false;
    ImagePicPathInfo                                   defaultPicPath;
    bool                                               transparent             = true;
    QPair<QString, QMap<QVariant, ImagePicPathInfo> >  propertyPicPaths;
};

#endif // IMAGEICONBUTTON_H



