#include "stringeditor.h"
#include <QLineEdit>

StringEditor::StringEditor(QObject *parent)
    : PropertyEditor(m_line = new QLineEdit, parent)
{
    connect(m_line, &QLineEdit::textEdited, this, &PropertyEditor::editorModified);
}

QVariant StringEditor::editorValue() const
{
    return m_line->text();
}

void StringEditor::setEditorValue(const QVariant& value)
{
    m_line->setText(value.toString());
}