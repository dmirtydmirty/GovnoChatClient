#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>
#include <QLabel>

class SettingsDialog : public QDialog {
    Q_OBJECT

    const QString defaultPath{"srv.json"};
    void readFile();
    void writeFile();
public:
    SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog() override;

    QPair<QString, int> getSettings() const;

private slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    QLineEdit *hostLineEdit;
    QSpinBox *portSpinBox;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QString host;
    quint32 port;
};

#endif // SETTINGSDIALOG_H
