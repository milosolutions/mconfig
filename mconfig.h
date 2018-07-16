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

#include <mbaseconfig.h>

#define CONFIG_VALUE(name, type) mValues.insert(#name, ValuePtr(type, static_cast<void *>(&name)));

class MConfig : public MBaseConfig
{
 public:
    MConfig(const QByteArray &groupName);
#ifdef MCRYPTO_LIB
    MConfig(const QByteArray &groupName, const QByteArray &passphrase);
#endif

 protected:
    QList<QByteArray> valueNames() const final;
    QVariant value(const QByteArray &name) const final;
    void setValue(const QByteArray &name, const QVariant &value) final;

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
    static void copyValue(void *dst, int type, const QVariant &value);
};
#endif  // MCONFIG_H
