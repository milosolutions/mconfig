#ifndef MMETACONFIGEDITOR_H
#define MMETACONFIGEDITOR_H

#include <QWidget>
#include <QVariant>

class QFormLayout;
class QHBoxLayout;
class QAbstractButton;
class MMetaConfig;
class PropertyEditor;

class MMetaConfigEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MMetaConfigEditor(QWidget *parent = nullptr);
    MMetaConfigEditor(MMetaConfig *config, QWidget *parent = nullptr);
    void setConfig(MMetaConfig *config);
    void setAutoLoad(bool on);
    void setAutoSave(bool on);
protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
private:
    void init();
    void addEditor(const char* name, QVariant::Type type);
    void loadAll();
    bool m_autoLoad{false};
    bool m_autoSave{false};
    QFormLayout *m_layout_editors;
    QHBoxLayout *m_layout_buttons;
    QAbstractButton *m_load;
    QAbstractButton *m_save;
    MMetaConfig *m_config{nullptr};
    QHash<const char*,PropertyEditor*> m_editors;
};

#endif // MMETACONFIGEDITOR_H