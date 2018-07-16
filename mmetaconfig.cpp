#include "mmetaconfig.h"
#include <QMetaProperty>

/*!
 * \class MMetaConfig
 * \brief MBaseConfig with all member registered as QObject properties
 *
 * Subclass of MBaseConfig that has registered all members as properties.
 * This allow to use automated ui for edition. Use macro M_MEMBER
 * or M_MEMBER_V to define all members. It its advised to avoid building
 * complex hierarchies of settings. Its better to subclass MMetaConfig directly.
 * In most cases cost of repeating the same member will be minimal.
 * Example:
 * \code
 * class SimpleConfig : public MMetaConfig
 * {
 *    Q_OBJECT
 *    M_OBJECT(SimpleConfig, "category_name")
 *    M_MEMBER(int value)
 *    M_MEMBER_V(QString text "default value")
 * };
 * \endcode
 */


MMetaConfig::MMetaConfig(const QByteArray &groupName) : MBaseConfig(groupName)
{
    // Nothing
}

#ifdef MCRYPTO_LIB
MMetaConfig::MMetaConfig(const QByteArray &groupName, const QByteArray &passphrase)
    : MBaseConfig(groupName, passphrase)
{
    // Nothing
}
#endif


QList<QByteArray> MMetaConfig::valueNames() const
{
    return m_names;
}

QVariant MMetaConfig::value(const QByteArray &name) const
{
    return property(name.constData());
}

void MMetaConfig::setValue(const QByteArray &name, const QVariant &value)
{
    setProperty(name.constData(), value);
}

/*!
 * Gather names of all properties for MBaseConfig.
 * Read only properties defined for this object.
 */
void MMetaConfig::init(const QMetaObject *object)
{
    for (int i = object->propertyOffset(); i < object->propertyCount(); ++i) {
        m_names.append(object->property(i).name());
    }
}