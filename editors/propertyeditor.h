#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QByteArray>
#include <QObject>
#include <QPointer>
#include <QVariant>

class QWidget;

class PropertyEditor : public QObject
{
    Q_OBJECT
 public:
    PropertyEditor(QWidget* widget, QObject *parent = nullptr);
    ~PropertyEditor();
    QWidget* widget() const;
    QVariant value() const;
    void setValue(const QVariant& value);

 signals:
    void editorModified() const;
    void valueChanged() const;

 protected:
    virtual QVariant editorValue() const = 0;
    virtual void setEditorValue(const QVariant& value) = 0;

 private:
    void onEditorModified();
    QPointer<QWidget> m_widget;
    QVariant m_value;
};

#endif  // PROPERTYEDITOR_H
