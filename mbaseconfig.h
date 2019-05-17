#ifndef MBASECONFIG_H
#define MBASECONFIG_H

#include <QByteArray>
#include <QHash>
#include <QMetaType>
#include <QSettings>
#include <QString>
#ifdef MCRYPTO_LIB
#include "mcrypto.h"
#endif

class MBaseConfig
{
public:
   MBaseConfig(const QByteArray &groupName);
#ifdef MCRYPTO_LIB
   MBaseConfig(const QByteArray &groupName, const QByteArray &passphrase);
   void setPassphrase(const QByteArray &pass);
#endif
   void load(const QString &fileName = QString(),
             const QSettings::Format &format = QSettings::IniFormat);
   void save(const QString &fileName = QString(),
             const QSettings::Format &format = QSettings::IniFormat);
   QString filePath() const;
   const QByteArray &groupName() const;

protected:
   virtual QList<QByteArray> valueNames() const = 0;
   virtual QVariant value(const QByteArray &name) const = 0;
   virtual void setValue(const QByteArray &name, const QVariant &value) = 0;

private:
   const QByteArray m_groupName;
   QString m_fileName;
#ifdef MCRYPTO_LIB
   MCrypto m_crypto;
   QByteArray m_passphrase;
#endif
};

#endif // MBASECONFIG_H
