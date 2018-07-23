#include "propertyeditor.h"
#include <QWidget>

/*!
 * \class PropertyEditor
 * \brief Lite version of PropertyEditor from Milo Tools
 *
 * Class provides interface that enhance QWidget with ability to
 * read and write QVariant value and track changes.
 */

/*!
 * \fn PropertyEditor::editorValue
 * \brief current value of editor
 *
 * This method must be always implemented in order to provide
 * value of specific editor as QVariant.
 */

/*!
 * \fn PropertyEditor::setEditorValue(const QVariant& value)
 * \brief set value of editor
 * \param value value that should be set
 *
 * This method must be always implemented by inheriting classes.
 * Method should set value of editor input widget. Method should never trigger
 * emmision of editorModified signal.
 */

/*!
 * \fn PropertyEditor::valueChanged
 * \brief notify that PropertyEditor::value has changed
 *
 * This signal is emited by setValue method and when editor input is accepted
 * \sa PropertyEditor::editorModified
 */

/*!
 * \fn PropertyEditor::editorModified
 * \brief notify about change in editors input
 *
 * Unlike PropertyEditor::valueChanged this signal should be emitted only if editor input was
 * modified directly by user.
 */

/*!
 * \brief constructor
 * \param widget pointer to QWidget based class that represent visual part of  PropertyEditor
 *
 * Constructor should be called in derrived objects contructors and provides
 * pointer to new widget. PropertyEditor takes ownership of this widget so
 * it should not have parent set, nor should it be deleted in derived class.
 *
 * ### Example
 *
 * Assuming PropertEditor will be represented by QTextLine, proper
 * call to base constructor in derived should looks like:
 * \code
 * PropertyEditor(new QTextLine)
 * \endcode
 * If in derived class it is required to get access to widget, then it is ok to pass assigment like this:
 * \code
 * class MyClass : public PropertyEditor
 * {
 * // ...
 * private:
 * QTextLine *textLine;
 * };
 *
 * // c-tor definition
 * MyClass() : PropertyEditor(textLine = new QTextLine)
 * {
 *     // ...
 * }
 * \endcode
 */
PropertyEditor::PropertyEditor(QWidget* widget, QObject *parent)
    : QObject(parent), m_widget(widget)
{
    connect(this, &PropertyEditor::editorModified, this, &PropertyEditor::onEditorModified);
}

/*!
 * \brief destructor
 *
 * PropertyEditor owns widget passed in constructor. If it was not deleted in layout
 * then PropertyEditor will release memory.
 */
PropertyEditor::~PropertyEditor()
{
    if (m_widget && !m_widget->parent()) delete m_widget;
}

/*!
 * \brief widget for editing value
 *
 * This method provide widget that can be used in some view.
 * Widget should be provided to constructor.
 */
QWidget* PropertyEditor::widget() const
{
    return m_widget;
}

QVariant PropertyEditor::value() const
{
    return m_value;
}

void PropertyEditor::setValue(const QVariant& value)
{
    m_value = value;
    setEditorValue(m_value);
    emit valueChanged();
}

/*!
 * \brief handle modification in editor
 *
 * New editorValue is validated and if its correct
 * value is updated.
 */
void PropertyEditor::onEditorModified()
{
    auto value = editorValue();
    if (value != m_value) {
        m_value = value;
        emit valueChanged();
    }
}
