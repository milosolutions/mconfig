#ifndef MMETACONFIG_H
#define MMETACONFIG_H

#include <QObject>
#include "mbaseconfig.h"

//Config member macro
#define M_MEMBER(type, name) \
public:                        \
   type name;                  \
                               \
private:                       \
   Q_PROPERTY(type name MEMBER name)

//Config member macro - default value
#define M_MEMBER_V(type, name, value) \
public:                                 \
   type name{value};                   \
                                        \
private:                                \
   Q_PROPERTY(type name MEMBER name)

class MMetaConfig : public QObject, public MBaseConfig
{
public:
    MMetaConfig(const QByteArray &groupName);
#ifdef MCRYPTO_LIB
    MMetaConfig(const QByteArray &groupName, const QByteArray &passphrase);
#endif
protected:
   const QList<QByteArray> valueNames() const final;
   QVariant value(const QByteArray &name) const final;
   void setValue(const QByteArray &name, const QVariant &value) final;
private:
    void init();
    QList<QByteArray> m_names;
};

#endif // MMETACONFIG_H