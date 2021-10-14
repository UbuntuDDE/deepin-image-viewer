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
#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QEvent>

#include "controller/viewerthememanager.h"
#include <dimagebutton.h>
#include <DLabel>

using namespace Dtk::Widget;
typedef DLabel QLbtoDLabel;

class ImageButton : public DImageButton
{
    Q_OBJECT
public:
    explicit ImageButton(QWidget *parent = nullptr);
    explicit ImageButton(const QString &normalPic, const QString &hoverPic,
                         const QString &pressPic, const QString &disablePic,
                         QWidget *parent = nullptr);

    void setDisabled(bool d);

    void setTooltipVisible(bool visible);

    inline const QString getDisablePic() const { return m_disablePic_; }
signals:
    void mouseLeave();

protected:
    void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
    bool event(QEvent *e) Q_DECL_OVERRIDE;

private:
    void showTooltip(const QPoint &gPos);
    void onThemeChanged(ViewerThemeManager::AppTheme theme);
private:
    bool m_tooltipVisiable;
    QString m_disablePic_;
};

#endif // IMAGEBUTTON_H
