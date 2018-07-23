/*******************************************************************************
Copyright (C) 2017 Milo Solutions
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

#include "mconfig.h"
#include <QDateTime>
#include <QPoint>
#include <QRect>
#include <QSettings>

/*!
 * \defgroup Config Configuration and settings
 * @{
 */

/*!
 * \class MConfig
 * \brief Configuration object base
 *
 * Class provides simplified use for storing configurable values.
 *
 * If you don't call save() values will not be stored in a file. This has no
 * overhead - you have just normal C++ member variables. When you call save(),
 * a config file is created using QSettings. To load data from config file, use
 * load().
 *
 * Thus, MConfig can be used as both application config (with .ini file) or
 * runtime-only config class. The choice is yours.
 *
 * Usage:
 * 1. Subclass Config
 * 2. Define group name (mGroupName)
 * 3. For each member of subclassed object provide info to mValues hash using ValuePtr object - see CONFIG_VALUE macro.
 * 4. Make sure yor application does have QCoreApplication::organizationName and
 * QCoreApplication::applicationName set.
 *
 *
 * \def CONFIG_VALUE
 * \brief simple initialization of mValues
 *
 * Register \a name member of class in mValues and associate it with provided \a type
 */

MConfig::MConfig(const QByteArray &groupName) : MBaseConfig(groupName)
{
    // Nothing
}

#ifdef MCRYPTO_LIB
MConfig::MConfig(const QByteArray &groupName, const QByteArray &passphrase)
    : MBaseConfig(groupName, passphrase)
{
    // Nothing
}
#endif

QList<QByteArray> MConfig::valueNames() const
{
    return mValues.keys();
}

QVariant MConfig::value(const QByteArray &name) const
{
    return QVariant(mValues.value(name).type, mValues.value(name).ptr);
}

void MConfig::setValue(const QByteArray &name, const QVariant &value)
{
    copyValue(mValues.value(name).ptr, mValues.value(name).type, value);
}

/*!
 * \brief copy variant value to given pointer using defined type
 * \param dst where value form variant should be copied
 * \param type type of value
 * \param value variant to be copied
 */

#define COPY_TYPE(type)                       \
    {                                         \
        type *ptr = static_cast<type *>(dst); \
        *ptr = value.value<type>();           \
    }                                         \
    break;

void MConfig::copyValue(void *dst, int type, const QVariant &value)
{
    if (value.isNull()) {
        return;
    }

    Q_ASSERT(value.canConvert(type));

    switch (type) {
        case QMetaType::Int:
            COPY_TYPE(int)
        case QMetaType::QByteArray:
            COPY_TYPE(QByteArray)
        case QMetaType::QString:
            COPY_TYPE(QString)
        case QMetaType::Bool:
            COPY_TYPE(bool)
        case QMetaType::Float:
            COPY_TYPE(float)
        case QMetaType::QPoint:
            COPY_TYPE(QPoint)
        case QMetaType::QPointF:
            COPY_TYPE(QPointF)
        case QMetaType::QRect:
            COPY_TYPE(QRect)
        case QMetaType::QRectF:
            COPY_TYPE(QRectF)
        case QMetaType::QDateTime:
            COPY_TYPE(QDateTime)
        default:
            qFatal("Config: type unsupported!");
    }
}

/*! @} */
