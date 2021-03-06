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
/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c DIVDBusController -p divdbuscontroller com.deepin.ImageViewer.xml
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DIVDBUSCONTROLLER_H
#define DIVDBUSCONTROLLER_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.deepin.ImageViewer
 */
class DIVDBusController: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceService()
    { return "com.deepin.ImageViewer"; }
    static inline const char *staticInterfacePath()
    { return "/com/deepin/ImageViewer"; }
    static inline const char *staticInterfaceName()
    { return "com.deepin.ImageViewer"; }
public:
    explicit DIVDBusController(QObject *parent = nullptr);

    ~DIVDBusController();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> activeWindow()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("activeWindow"), argumentList);
    }

    inline QDBusPendingReply<> backToMainWindow()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("backToMainWindow"), argumentList);
    }

    inline QDBusPendingReply<> editImage(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("editImage"), argumentList);
    }

    inline QDBusPendingReply<> enterAlbum(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("enterAlbum"), argumentList);
    }

    inline QDBusPendingReply<> searchImage(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("searchImage"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace com {
namespace deepin {
typedef ::DIVDBusController DeepinImageViewer;
}
}
#endif
