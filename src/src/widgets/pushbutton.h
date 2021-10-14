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
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "controller/viewerthememanager.h"
#include <QWidget>

class PushButton : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    explicit PushButton(QWidget *parent = nullptr);

    QString normalPic() const;
    QString hoverPic() const;
    QString pressPic() const;
    QString disablePic() const;
    QString checkedPic() const;

    QString text() const;
    QColor normalColor() const;
    QColor hoverColor() const;
    QColor pressColor() const;
    QColor disableColor() const;

    void setChecked(bool checked);


public slots:

    void setText(QString text);


signals:
    void normalPicChanged(QString normalPic);
    void hoverPicChanged(QString hoverPic);
    void pressPicChanged(QString pressPic);
    void disablePicChanged(QString disablePic);
    void textChanged(QString text);

    void normalColorChanged(QColor normalColor);
    void hoverColorChanged(QColor hoverColor);
    void pressColorChanged(QColor pressColor);
    void disableColorChanged(QColor disableColor);

    void clicked();
    void mouseLeave();

    void checkedPicChanged(QString checkedPic);

protected:
    bool event(QEvent *e) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;

private:
    QString getPixmap() const;
    QColor getTextColor() const;

    void showTooltip(const QPoint &pos);
    void onThemeChanged(ViewerThemeManager::AppTheme theme);

private:
    QString m_normalPic;
    QString m_hoverPic;
    QString m_pressPic;
    QString m_disablePic;
    QString m_text;
    QColor m_normalColor;
    QColor m_hoverColor;
    QColor m_pressColor;
    QColor m_disableColor;

    QString m_currentPic;
    QColor m_currentColor;

    bool m_checked;
    bool m_isPressed;
    int m_spacing;
    QString m_checkedPic;
};

#endif // PUSHBUTTON_H
