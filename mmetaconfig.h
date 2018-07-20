#ifndef MMETACONFIG_H
#define MMETACONFIG_H

#include <QObject>
#include "mbaseconfig.h"

// Category macro
#define M_OBJECT(object) \
public:                            \
    object() : MMetaConfig(#object) { init(metaObject()); }

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
    Q_OBJECT
public:
    MMetaConfig(const QByteArray &groupName);
#ifdef MCRYPTO_LIB
    MMetaConfig(const QByteArray &groupName, const QByteArray &passphrase);
#endif
protected:
   QList<QByteArray> valueNames() const final;
   QVariant value(const QByteArray &name) const final;
   void setValue(const QByteArray &name, const QVariant &value) final;
   void init(const QMetaObject *object);
private:
    QList<QByteArray> m_names;
};

#endif // MMETACONFIG_H