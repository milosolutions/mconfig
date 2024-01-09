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
 *    M_OBJECT(SimpleConfig)
 *    M_MEMBER(int value)
 *    M_MEMBER_V(QString text "default value")
 * };
 * \endcode
 *
 * ### Automatic load and save
 * It might be useful to have config object load data from QSettings storage on construction and save them on deletion. It can be enabled by replacing macro M_OBJECT with M_OBJECT_AUTOLOADSAVE. 
 * Config classes designed this way require only header file.
 * 
 * QML support
 * MMetaConfig iherits QObject and every member is declared as Q_PROPERTY. Therefore if you expose QObject pointer to config to qml context you can read and modify all members.
 *
 * ### Hint on member naming
 * There is no limitation on member names. However MMetaConfigEditor is designed in
 * a way that will replace "_" in name with space (" "). This allow for nice ui generation.
 * So your property is named "path_to_important_file" in MMetaConfig based class,
 * then MMetaConfigEditor will produce label "path to important file".
 */


MMetaConfig::MMetaConfig(const QByteArray &groupName) : MBaseConfig(groupName)
{
    // Nothing
}

#ifdef CRYPTED_CONFIG
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
 * Read only properties defined for this object and subclasses.
 */
void MMetaConfig::init(const QMetaObject *object)
{
    for (int i = object->propertyOffset(); i < object->propertyCount(); ++i) {
        m_names.append(object->property(i).name());
    }
}
