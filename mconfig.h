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

#ifndef MCONFIG_H
#define MCONFIG_H

#include <QByteArray>
#include <QHash>
#include <QMetaType>
#include <QSettings>
#include <QString>
#ifdef MCRYPTO_LIB
#include "mcrypto.h"
#endif

#define CONFIG_VALUE(name, type) mValues.insert(#name, ValuePtr(type, static_cast<void *>(&name)));

class MConfig
{
 public:
    MConfig(const QByteArray &groupName);
#ifdef MCRYPTO_LIB
    MConfig(const QByteArray &groupName, const QByteArray &passphrase);
    void setPassphrase(const QByteArray &pass);
#endif
    void load(const QString &fileName = QString(),
              const QSettings::Format &format = QSettings::IniFormat);
    void save(const QString &fileName = QString(),
              const QSettings::Format &format = QSettings::IniFormat);
    QString filePath() const;
    const QByteArray &groupName() const;

 protected:
    class ValuePtr
    {
     public:
        ValuePtr() {}
        ValuePtr(int t, void *v) : type(t), ptr(v) {}
        int type = QMetaType::UnknownType;
        void *ptr = nullptr;
    };
    QHash<QByteArray, ValuePtr> mValues;

 private:
    const QByteArray mGroupName;
    QString mFileName;
    static void copyValue(void *dst, int type, const QVariant &value);

#ifdef MCRYPTO_LIB
    MCrypto mcrypto;
    QByteArray mPassphrase;
#endif
};
#endif  // MCONFIG_H
