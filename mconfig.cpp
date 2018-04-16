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
 * 3. For each member of subclassed object provide info to mValues hash using ValuePtr object.
 * 4. Make sure yor application does have QCoreApplication::organizationName and
 * QCoreApplication::applicationName set.
 */

/*!
 * \param groupName group name for QSettings
 * \sa groupName
 */
MConfig::MConfig(const QByteArray &groupName) : mGroupName(groupName)
{
    // Nothing
}

#ifdef MCRYPTO_LIB
/*!
 * \param groupName group name for QSettings
 * \param passphrase secret password that will be used for encryption.
 * 
 * Using this constructor will be useful if you want to call load method in constructor of derived class
 * and expect file to be encrypted. Available only if MCrypto module is added to project.
 * \sa groupName, setPassphrase
 */
MConfig::MConfig(const QByteArray &groupName, const QByteArray &passphrase)
    : mGroupName(groupName), mcrypto(MCrypto::AES_256, MCrypto::CBC), mPassphrase(passphrase)
{
    // Nothing
}

/*!
 * \brief Sets passphrase for encrypting config
 * \param Encryption passphrase
 * 
 * Providing passphrase means that configuration file will be encrypted if you call save method.
 * Available only if MCrypto module is added to project.
 */
void MConfig::setPassphrase(const QByteArray &pass)
{
    mPassphrase = pass;
}
#endif

/*!
 * \brief load settings from
 * \param fileName path to settings file
 * \param format format of settings file
 * 
 * If \a fileName is empty default location will be used. Its specific for operating system.
 * See [QSettings documentation](http://doc.qt.io/qt-5/qsettings.html#QSettings-4) for details.
 * If file is encrypted you must provide password before calling this method.
 */
void MConfig::load(const QString &fileName, const QSettings::Format &format)
{
    auto loadFrom = [this](QSettings &settings) {
        settings.beginGroup(mGroupName);
        for (const auto &key : mValues.keys()) {
            auto value = settings.value(key);
#ifdef MCRYPTO_LIB
            if (mPassphrase.size()) {
                auto key_enc = mcrypto.encrypt(key, mPassphrase);
                value = mcrypto.decrypt(settings.value(key_enc).toByteArray(), mPassphrase);
            }
#endif
            copyValue(mValues.value(key).ptr, mValues.value(key).type, value);
        }
    };

    if (fileName.isNull()) {
        QSettings settings;
        loadFrom(settings);
    } else {
        QSettings settings(fileName, format);
        loadFrom(settings);
        mFileName = fileName;
    }
}
/*!
 * \brief save settings to file
 * \param fileName path to settings file
 * \param format format of settings file
 * 
 * If \a fileName is empty default location will be used. Its specific for operating system.
 * See [QSettings documentation](http://doc.qt.io/qt-5/qsettings.html#QSettings-4) for details.
 * If file is meant to be encrypted you must provide password before calling this method.
 */
void MConfig::save(const QString &fileName, const QSettings::Format &format)
{
    auto saveTo = [this](QSettings &settings) {
        settings.beginGroup(mGroupName);
        for (auto key : mValues.keys()) {
            auto value = QVariant(mValues.value(key).type, mValues.value(key).ptr);
#ifdef MCRYPTO_LIB
            if (mPassphrase.size()) {
                key = mcrypto.encrypt(key, mPassphrase);
                value = mcrypto.encrypt(value.toByteArray(), mPassphrase);
            }
#endif
            settings.setValue(key, value);
        }
    };

    if (fileName.isNull()) {
        QSettings settings;
        saveTo(settings);
    } else {
        QSettings settings(fileName, format);
        saveTo(settings);
    }
}

/*!
 * Returns path to file where settings are being saved.
 *
 * WARNING: path will be returned even if you don't actually call save() anywhere
 * (in which case the settings file will not be present at returned location).
 * See also [QSettings documentation](http://doc.qt.io/qt-5/qsettings.html#fileName)
 */
QString MConfig::filePath() const
{
    return mFileName.isNull() ? QSettings().fileName() : mFileName;
}

/*!
 * \brief current QSettings group name
 * 
 * This is group into which this object will save or load from.
 * See [QSettings documentation](http://doc.qt.io/qt-5/qsettings.html#beginGroup) for more  details.
 */
const QByteArray &MConfig::groupName() const
{
    return mGroupName;
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
