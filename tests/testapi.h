#ifndef TESTAPI_H
#define TESTAPI_H

#include <QString>
#include <QProcess>
#include "application.h"
#include <QMimeData>
#include <QWidget>
#include <QUrl>
#include <QDragEnterEvent>
#include <QTest>

class TestApi
{
public:
    TestApi();

static bool drogPathtoWidget(QWidget *panel,const QString& path)
{
    bool iRet=false;
    if(panel){
        QString TriangleItemPath = path;

        QMimeData mimedata;
        QList<QUrl> li;
        li.append(QUrl::fromLocalFile(TriangleItemPath));

        mimedata.setUrls(li);

        const QPoint pos = QPoint(panel->pos().x()+200,panel->pos().y()+200);
        QDragEnterEvent eEnter(pos, Qt::IgnoreAction, &mimedata, Qt::LeftButton, Qt::NoModifier);
        qApp->sendEvent(panel, &eEnter);

        QDropEvent e(pos, Qt::IgnoreAction, &mimedata, Qt::LeftButton, Qt::NoModifier);
        qApp->sendEvent(panel, &e);

        iRet = true;
    }
    return iRet;

}
};
#endif // TESTAPI_H


