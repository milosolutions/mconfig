#include "mmetaconfigeditor.h"
#include "mmetaconfig.h"
#include <QBoxLayout>
#include <QFormLayout>
#include <QMetaProperty>
#include <QLabel>
#include <QPushButton>
#include "editors/propertyeditor.h"
#include "editors/stringeditor.h"

/*!
 * \class MConfigEditor
 * \brief Universal editor for MMetaConfig objects
 *
 * Provides basic edition of config object.
 * Each property is presented as label with suitable editor in form layout.
 */


MMetaConfigEditor::MMetaConfigEditor(QWidget *parent) : QWidget(parent)
{
    init();
}

MMetaConfigEditor::MMetaConfigEditor(MMetaConfig *config, QWidget *parent) : QWidget(parent)
{
    init();
    load(config);
}

void MMetaConfigEditor::load(MMetaConfig *config)
{
    Q_ASSERT(!m_config);
    m_config = config;

    auto object = m_config->metaObject();
    for (int i = object->propertyOffset(); i < object->propertyCount(); ++i) {
        auto p = object->property(i);
        addEditor(p.name(), p.type());
    }
}

/*!
 * \brief auto load mode
 *
 * If auto load is enabled, config is loaded from QSetting storage
 * each time this widget is shown. If mode is disabled, "Load" button appears
 * and it must be clicked manually. Default: disabled.
 */
void MMetaConfigEditor::setAutoLoad(bool on)
{
    if (on != m_autoLoad) {
        m_load->setVisible(!on);
        m_autoLoad = on;
    }
}

/*!
 * \brief auto save mode
 *
 * If auto save is enabled. config is saved to QSettings storage
 * each time this widget is hidden. If mode is disabled, "Save" button appears
 * and it must be clicked manually. Default: disabled.
 */
void MMetaConfigEditor::MMetaConfigEditor::setAutoSave(bool on)
{
    if (on != m_autoSave) {
        m_save->setVisible(!on);
        m_autoSave = on;
    }
}


void MMetaConfigEditor::showEvent(QShowEvent *event)
{
    if (m_autoLoad) loadAll();
    QWidget::showEvent(event);
}

void MMetaConfigEditor::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);
    if (m_autoSave && m_config) m_config->save();
}

void MMetaConfigEditor::init()
{
    m_layout_editors = new QFormLayout;
    m_layout_buttons = new QHBoxLayout;
    m_layout_buttons->addStretch();
    m_load = new QPushButton(this);
    m_load->setText(tr("Load"));
    m_load->setToolTip(tr("Load settings on this page"));
    m_layout_buttons->addWidget(m_load);
    connect(m_load, &QAbstractButton::clicked, this, [this](){
        if (m_config) loadAll();
    });
    m_save = new QPushButton(this);
    m_save->setText(tr("Save"));
    m_save->setToolTip(tr("Save settings on this page"));
    m_layout_buttons->addWidget(m_save);
    connect(m_save, &QAbstractButton::clicked, this, [this](){
        if (m_config) m_config->save();
    });

    auto layout = new QVBoxLayout(this);
    layout->addLayout(m_layout_editors);
    layout->addLayout(m_layout_buttons);
}

void MMetaConfigEditor::addEditor(const char* name, QVariant::Type type)
{
    PropertyEditor *editor;
    switch (type) {
    //TODO use more types (spinbox, datepicker)
    case QVariant::String:
    default:
        editor = new StringEditor(this);
    }
    connect(editor, &PropertyEditor::editorModified, this, [this, name, editor](){
        m_config->setProperty(name, editor->value());
    });

    m_layout_editors->addRow(new QLabel(QString(name).replace("_", " ")), editor->widget());
    m_editors.insert(name, editor);
}

void MMetaConfigEditor::loadAll()
{
    if (!m_config) return;
    m_config->load();

    for (const auto& key : m_editors.keys()) {
        auto editor = m_editors.value(key);
        editor->setValue(m_config->property(key));
    }
}
