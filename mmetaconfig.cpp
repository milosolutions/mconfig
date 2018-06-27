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
 *    M_MEMBER(int value)
 *    M_MEMBER_V(QString text "default value")
 * public:
 *    SimpleConfig() : MMetaConfig("category_name") {}
 * };
 * \endcode
 */


MMetaConfig::MMetaConfig(const QByteArray &groupName) : MBaseConfig(groupName)
{
    init();
}

#ifdef MCRYPTO_LIB
MMetaConfig::MMetaConfig(const QByteArray &groupName, const QByteArray &passphrase)
    : MBaseConfig(groupName, passphrase)
{
    init();
}
#endif


const QList<QByteArray> MMetaConfig::valueNames() const
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
void MMetaConfig::init()
{
    for (int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); ++i) {
        m_names.append(metaObject()->property(i).name());
    }
}