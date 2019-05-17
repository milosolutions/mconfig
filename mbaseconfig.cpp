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

#include "mbaseconfig.h"
#include <QDateTime>
#include <QPoint>
#include <QRect>
#include <QSettings>

/*!
 * \defgroup Config Configuration and settings
 * @{
 */

/*!
 * \class MBaseConfig
 * \brief Configuration object base
 *
 * This abstract base simplifies loading and saving values to QSettings.
 * With help of MCrypto it encrypts all content.
 * There are two implementations provided:
 * * MConfig - aimed for minimal overhead
 * * MMetaConfig - designed for easier ui automation
 *
 *
 * \fn MBaseConfig::valueNames
 * \brief names of all values in this settings object
 *
 * You must implement this class if you provide your implementation of MBaseConfig interface.
 *
 *
 * \fn MBaseConfig::value
 * \brief return value of setting designated with given \a name
 *
 * You must implement this class if you provide your implementation of MBaseConfig interface.
 *
 *
 * \fn MBaseConfig::setValue
 * \brief set \a name setting to \a value
 *
 * You must implement this class if you provide your implementation of MBaseConfig interface.
 */

MBaseConfig::MBaseConfig(const QByteArray &groupName) : m_groupName(groupName)
{
    // Nothing
}

#ifdef MCRYPTO_LIB
MBaseConfig::MBaseConfig(const QByteArray &groupName, const QByteArray &passphrase)
    : m_groupName(groupName), m_gassphrase(passphrase)
{
    // Nothing
}

/*!
 * \brief Sets passphrase for encrypting config
 * \param Encryption passphrase
 *
 * Keep in mind that it makes sense to set password if you did not use load/save yet.
 * Also developer must be aware if data he is loading are encrypted or not.
 */
void MBaseConfig::setPassphrase(const QByteArray &pass)
{
    m_passphrase = pass;
}
#endif

/*!
 * \brief MBaseConfig::load - overloaded function that allows load settings from specified file and
 * format
 * \param fileName
 * \param format
 */
void MBaseConfig::load(const QString &fileName, const QSettings::Format &format)
{
    auto loadFrom = [this](QSettings &settings) {
        settings.beginGroup(m_groupName);
        const auto &values = valueNames();
        for (const auto &key : values) {
            auto val = settings.value(key);
#ifdef MCRYPTO_LIB
            if (m_passphrase.size()) {
                auto key_enc = m_crypto.encrypt(key, m_passphrase);
                val = m_crypto.decrypt(settings.value(key_enc).toByteArray(),
                                       m_passphrase);
            }
#endif
            setValue(key, val);
        }
    };

    if (fileName.isNull()) {
        QSettings settings;
        loadFrom(settings);
    } else {
        QSettings settings(fileName, format);
        loadFrom(settings);
        m_fileName = fileName;
    }
}

/*!
 * \brief MBaseConfig::save - overloaded function that allows save settings in specified file and format
 * \param fileName
 * \param format
 */
void MBaseConfig::save(const QString &fileName, const QSettings::Format &format)
{
    auto saveTo = [this](QSettings &settings) {
        settings.beginGroup(m_groupName);
        const auto &values = valueNames();
        for (auto key : values) {
            auto val = value(key);
#ifdef MCRYPTO_LIB
            if (m_passphrase.size()) {
                key = m_crypto.encrypt(key, m_passphrase);
                val = m_crypto.encrypt(val.toByteArray(), m_passphrase);
            }
#endif
            settings.setValue(key, val);
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
 */
QString MBaseConfig::filePath() const
{
    return m_fileName.isNull() ? QSettings().fileName() : m_fileName;
}

const QByteArray &MBaseConfig::groupName() const
{
    return m_groupName;
}

/*! @} */
