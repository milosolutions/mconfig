/*******************************************************************************
Copyright (C) 2016 Milo Solutions
Contact: https://www.milosolutions.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/


#include "miloconfig.h"
#include <QSettings>
#include <QPoint>
#include <QRect>
#include <QDateTime>

/*!
 * \defgroup Config Configuration and settings
 * @{
 */

/*!
 * \class MiloConfig
 * \brief Configuration object base
 *
 * Class provides simplified use for storing configurable values.
 *
 * If you don't call save() values will not be stored in a file. This has no
 * overhead - you have just normal C++ member variables. When you call save(),
 * a config file is created using QSettings. To load data from config file, use
 * load().
 *
 * Thus, MiloConfig can be used as both application config (with .ini file) or
 * runtime-only config class. The choice is yours.
 *
 * Usage:
 * 1. Subclass Config
 * 2. Define group name (mGroupName)
 * 3. For each member of subclassed object provide info to mValues hash using ValuePtr object.
 * 4. Make sure yor application does have QCoreApplication::organizationName and
 * QCoreApplication::applicationName set.
 */

MiloConfig::MiloConfig(const QByteArray& groupName) :
    mGroupName(groupName)
{
    //Nothing
}

/*!
 * \brief load all values using QSettings
 */
void MiloConfig::load()
{
    QSettings settings;
    settings.beginGroup(mGroupName);
    foreach (const QByteArray& key, mValues.keys()) {
        copyValue(mValues.value(key).ptr,
                  mValues.value(key).type,
                  settings.value(key));
    }
}
/*!
 * \brief MiloConfig::load - overloaded function that allows load settings from specified file and format
 * \param fileName
 * \param format
 */
void MiloConfig::load(const QString &fileName, const QSettings::Format &format)
{
    QSettings settings(fileName, format);
    settings.beginGroup(mGroupName);
    foreach (const QByteArray& key, mValues.keys()) {
        copyValue(mValues.value(key).ptr,
                  mValues.value(key).type,
                  settings.value(key));
    }
}

/*!
 * \brief save all values using QSettings
 */
void MiloConfig::save()
{
    QSettings settings;
    settings.beginGroup(mGroupName);
    foreach (const QByteArray& key, mValues.keys()) {
        QVariant value(mValues.value(key).type,
                       mValues.value(key).ptr);
        settings.setValue(key, value);
    }
}
/*!
 * \brief MiloConfig::save - overloaded function that allows save settings in specified file and format
 * \param fileName
 * \param format
 */
void MiloConfig::save(const QString &fileName, const QSettings::Format &format)
{
    QSettings settings(fileName, format);
    settings.beginGroup(mGroupName);
    foreach (const QByteArray& key, mValues.keys()) {
        QVariant value(mValues.value(key).type,
                       mValues.value(key).ptr);
        settings.setValue(key, value);
    }
}

/*!
 * Returns path to file where settings are being saved.
 *
 * WARNING: path will be returned even if you don't actually call save() anywhere
 * (in which case the settings file will not be present at returned location).
 */
QString MiloConfig::filePath() const
{
    return QSettings().fileName();
}

/*!
 * \brief copy variant value to given pointer using defined type
 * \param dst where value form variant should be copied
 * \param type type of value
 * \param value variant to be copied
 */

#define COPY_TYPE(type) \
{\
    type *ptr = static_cast<type*>(dst);\
    *ptr = value.value<type>();\
} break;

void MiloConfig::copyValue(void *dst, int type, const QVariant& value)
{
    if (value.isNull()) {
        return;
    }

    Q_ASSERT(value.canConvert(type));

    switch (type) {
    case QMetaType::Int:        COPY_TYPE(int)
    case QMetaType::QByteArray: COPY_TYPE(QByteArray)
    case QMetaType::QString:    COPY_TYPE(QString)
    case QMetaType::Bool:       COPY_TYPE(bool)
    case QMetaType::Float:      COPY_TYPE(float)
    case QMetaType::QPoint:     COPY_TYPE(QPoint)
    case QMetaType::QPointF:    COPY_TYPE(QPointF)
    case QMetaType::QRect:      COPY_TYPE(QRect)
    case QMetaType::QRectF:     COPY_TYPE(QRectF)
    case QMetaType::QDateTime:  COPY_TYPE(QDateTime)
    default:
        qFatal("Config: type unsupported!");
    }
}

/*! @} */
