/*******************************************************************************
  Copyright (C) 2016 Milo Solutions
  Contact: https://www.milosolutions.com

  This file is part of Milo Code Database, which is a collection of useful code
  snippets often reused within Milo Solutions. As such, this code is present in
  many projects done by Milo Solutions and does not constitute a copyright
  infridgement.

  You are entitled to do anything you please with this code, just as with the
  rest of code you bought. Files not containing this notice were written
  specifically for this project and have not been shared with any other party
  within or without Milo.
*******************************************************************************/

#ifndef MILOCONFIG_H
#define MILOCONFIG_H

#include <QHash>
#include <QByteArray>
#include <QString>
#include <QMetaType>
#include <QSettings>

#define CONFIG_VALUE(name, type) \
        mValues.insert(#name, ValuePtr(type, static_cast<void*>(&name)));

class MiloConfig
{
public:
    MiloConfig(const QByteArray& groupName);
    void load();
    void load(const QString &fileName, const QSettings::Format &format = QSettings::IniFormat);
    void save();
    void save(const QString &fileName, const QSettings::Format &format = QSettings::IniFormat);

    QString filePath() const;

protected:
    class ValuePtr {
    public:
        ValuePtr() {}
        ValuePtr(int t, void* v) : type(t), ptr(v) {}
        int type = QMetaType::UnknownType;
        void* ptr = nullptr;
    };
    QHash<QByteArray,ValuePtr> mValues;
private:
    const QByteArray mGroupName;
    static void copyValue(void *dst, int type, const QVariant& value);
};
#endif // MILOCONFIG_H
