///*
// * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
// *
// * Author:     LiuMingHang <liuminghang@uniontech.com>
// *
// * Maintainer: ZhangYong <ZhangYong@uniontech.com>
// *
// * This program is free software: you can redistribute it and/or modify
// * it under the terms of the GNU General Public License as published by
// * the Free Software Foundation, either version 3 of the License, or
// * any later version.
// *
// * This program is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with this program.  If not, see <http://www.gnu.org/licenses/>.
// */
//#ifndef IMPORTER_H
//#define IMPORTER_H

//#include "dbmanager.h"
//#include <QFileInfo>
//#include <QFutureWatcher>
//#include <QObject>
//#include <QThread>

//class DirCollectThread : public QThread
//{
//    Q_OBJECT
//public:
//    DirCollectThread(const QString &root, const QString &album);
//    void run() Q_DECL_OVERRIDE;
//    void setStop(bool stop);
//    const QString dir() const;

//signals:
//    void currentImport(const QString &path);
//    void resultReady(const DBImgInfoList &infos);
//    void insertAlbumRequest(const QString &album, const QStringList &paths);

//private:
//    QString m_album;
//    QString m_root;
//    bool m_stop;
//};


//class FilesCollectThread : public QThread
//{
//    Q_OBJECT
//public:
//    FilesCollectThread(const QStringList &paths, const QString &album);
//    void run() Q_DECL_OVERRIDE;
////    void setStop(bool stop);

//signals:
//    void currentImport(const QString &path);
//    void resultReady(const DBImgInfoList &infos);
//    void insertAlbumRequest(const QString &album, const QStringList &paths);
//private:
//    QString m_album;
//    QStringList m_paths;
//    bool m_stop;
//};


//class Importer : public QObject
//{
//    Q_OBJECT
//public:
//    static Importer *instance();
//    explicit Importer(QObject *parent = nullptr);
//    bool isRunning() const;
//    void appendDir(const QString &path, const QString &album = "");
////    void appendFiles(const QStringList &paths, const QString &album = "");
////    void stop();
//    void stopDirCollect(const QString &dir);
////    void showImportDialog(const QString &album = "");

//signals:
//    void currentImport(const QString &path);
//    void imported(bool success);
//    void progressChanged();

//private:
//    QList<QThread *> m_threads;
//    QStringList m_dirs;
//    static Importer* m_importer;
//};

//#endif // IMPORTER_H
