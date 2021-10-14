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
#ifndef UNIONIMAGE_H
#define UNIONIMAGE_H

#include <QtCore/qglobal.h>

#if defined(UNIONIMAGE_LIBRARY)
#  define UNIONIMAGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define UNIONIMAGESHARED_EXPORT Q_DECL_IMPORT
#endif

#include <QHash>
#include <QString>
#include <QByteArray>
#include <QImage>
#include <QFileInfo>
#include <QStringList>
#include <QMap>
#include <FreeImage.h>

namespace  UnionImage_NameSpace {

enum SupportType {
    UNKNOWNTYPE = 0,    // unknown type
    BITMAP      = 1,    // standard image               : 1-, 4-, 8-, 16-, 24-, 32-bit
    UINT16      = 2,    // array of unsigned short      : unsigned 16-bit
    INT16       = 3,    // array of short               : signed 16-bit
    UINT32      = 4,    // array of unsigned long       : unsigned 32-bit
    INT32       = 5,    // array of long                : signed 32-bit
    FLOAT       = 6,    // array of float               : 32-bit IEEE floating point
    DOUBLE      = 7,    // array of double              : 64-bit IEEE floating point
    COMPLEX     = 8,    // array of FICOMPLEX           : 2 x 64-bit IEEE floating point
    RGB16       = 9,    // 48-bit RGB image             : 3 x 16-bit
    RGBA16      = 10,   // 64-bit RGBA image            : 4 x 16-bit
    RGBF        = 11,   // 96-bit RGB float image       : 3 x 32-bit IEEE floating point
    RGBAF       = 12    // 128-bit RGBA float image     : 4 x 32-bit IEEE floating point
};

///**
// ************************************************************************************************
// *                                                                                              *
// *  Function name:                                                                              *
// *                                                                                              *
// *                                                                                              *
// *                                                                                              *
// *                                                                                              *
// *                                                                                              *
// *                                                                                              *
// *                                                                                              *
// ************************************************************************************************
// */
//UNIONIMAGESHARED_EXPORT QString unionImageVersion();


/**
 * @brief UnionImageSupporFormat
 * @return const QStringList
 * @author DJH
 * 返回UnionImage支持的所有格式
 * StaticFormat返回支持的静态图片
 * DynamicFormat返回支持的动态图片
 */
UNIONIMAGESHARED_EXPORT const QStringList unionImageSupportFormat();
//UNIONIMAGESHARED_EXPORT const QStringList supportStaticFormat();
//UNIONIMAGESHARED_EXPORT const QStringList supportMovieFormat();

/**
 * @brief suffixisImage
 * @return const bool
 * @author lmh
 * 从后缀名称判断是否为一张图片（包括损坏和不支持图片）
 */
UNIONIMAGESHARED_EXPORT bool suffixisImage(const QString &path);

UNIONIMAGESHARED_EXPORT bool isDynamicFormat();
///**
// * @brief CreatNewImage
// * @param[out]          res
// * @param[in]           width
// * @param[in]           height
// * @param[in]           depth
// * @param[in]           type
// * @return bool
// * @author DJH
// * 创建一个可以自定义深度和颜色空间的图片
// */
//UNIONIMAGESHARED_EXPORT bool creatNewImage(QImage &res, int width = 0, int height = 0, int depth = 0, SupportType type = UNKNOWNTYPE);

/**
 * @brief LoadImageFromFile
 * @param[in]           path
 * @param[out]          res
 * @param[out]          realSize
 * @param[out]          errorMsg
 * @return bool
 * @author DJH
 * 从文件载入图片
 * 载入成功返回true，图片数据返回到res
 * 载入失败返回false，如果需要可以读取errorMsg返回错误信息
 * 载入动态图片时，只会返回动态图片的第一帧，如果需要动图请使用UnionDynamicImage
 * 当res传入前设置了大小的时候，会尝试直接按照此大小读取图片（如果尝试失败则直接读取全图），此时图片的真实大小存放在realSize中
 */
UNIONIMAGESHARED_EXPORT bool loadStaticImageFromFile(const QString &path, QImage &res, QSize &realSize, QString &errorMsg, const QString &format_bar = "");

/**
 * @brief detectImageFormat
 * @param path
 * @return QString
 * 返回图片的真格式
 */
UNIONIMAGESHARED_EXPORT QString detectImageFormat(const QString &path);

FREE_IMAGE_FORMAT detectImageFormat_f(const QString &path);
///**
// * @brief isNoneQImage
// * @param[in]           qi
// * @return bool
// * @author DJH
// * 判断是否为空图
// */
//UNIONIMAGESHARED_EXPORT bool isNoneQImage(const QImage &qi);

/**
 * @brief rotateImage
 * @param[in]           angel
 * @param[out]          image
 * @return bool
 * @author DJH
 * 在内存中旋转图片
 */
UNIONIMAGESHARED_EXPORT bool rotateImage(int angel, QImage &image);

/**
 * @brief rotateImageFIle
 * @param[in]           angel
 * @param[in]           path
 * @param[out]          erroMsg
 * @return bool
 * @author DJH
 * 旋转图片文件，旋转成功返回true，失败返回false
 * 当不需要获取旋转图片的结果或者只有文件地址时调用该函数
 * 失败时会将错误信息写入erroMsg
 */
UNIONIMAGESHARED_EXPORT bool rotateImageFIle(int angel, const QString &path, QString &erroMsg);

///**
// * @brief rotateImageFIle
// * @param[in]           angel
// * @param[in][out]      img
// * @param[in]           path
// * @param[out]          erroMsg
// * @return bool
// * @author DJH
// * 旋转图片文件，旋转成功返回true，失败返回false
// * 旋转成功会同时旋转img
// * 图片为空则不会旋转返回失败,失败时会将错误信息写入erroMsg
// */
//UNIONIMAGESHARED_EXPORT bool rotateImageFIleWithImage(int angel, QImage &img, const QString &path, QString &erroMsg);

/**
 * @brief getAllMetaData
 * @param path
 * @author LMH
 * @return QMap<QString, QString>
 * 获取图片的所有数据,包括创建时间、修改时间、大小等
 */
UNIONIMAGESHARED_EXPORT QMap<QString, QString> getAllMetaData(const QString &path);

/**
 * @brief isImageSupportRotate
 * @param path
 * @author LMH
 * @return bool
 * 图片是否可以旋转
 */
UNIONIMAGESHARED_EXPORT bool isImageSupportRotate(const QString &path);

/**
 * @brief canSave
 * @param path
 * @author LMH
 * @return bool
 * 图片是否可以保存
 */
UNIONIMAGESHARED_EXPORT bool canSave(const QString &path);

//UNIONIMAGESHARED_EXPORT bool isSupportReading(const QString &path);

UNIONIMAGESHARED_EXPORT bool isSupportWritting(const QString &path);

/**
 * @brief getOrientation
 * @param path
 * @author LMH
 * @return QString
 * 获得图片的数据
 */
UNIONIMAGESHARED_EXPORT const QString getOrientation(const QString &path);

/**
 * @brief string2DateTime
 * @param QString
 * @author LMH
 * @return QDateTime
 * 转换时间
 */
//UNIONIMAGESHARED_EXPORT QDateTime string2DateTime(const QString &time);


UNIONIMAGESHARED_EXPORT bool isSupportsReading(const QString &time);

//UNIONIMAGESHARED_EXPORT bool isSupportsWriting(const QString &time);

UNIONIMAGESHARED_EXPORT bool getThumbnail(QImage &res, const QString &path);

QT_BEGIN_NAMESPACE



QT_END_NAMESPACE

};


#endif // UNIONIMAGE_H
