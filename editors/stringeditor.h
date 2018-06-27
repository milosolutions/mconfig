#ifndef STRINGEDITOR_H
#define STRINGEDITOR_H

#include "propertyeditor.h"

class QLineEdit;

class StringEditor : public PropertyEditor
{
public:
    StringEditor(QObject *parent = nullptr);
protected:
    QVariant editorValue() const final;
    void setEditorValue(const QVariant& value) final;
private:
    QLineEdit * m_line;
};

#endif // STRINGEDITOR_H