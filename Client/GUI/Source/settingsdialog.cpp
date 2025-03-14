#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Settings");

    QLabel *hostLabel = new QLabel("Host:");
    hostLineEdit = new QLineEdit();
    QLabel *portLabel = new QLabel("Port:");
    portSpinBox = new QSpinBox();
    portSpinBox->setRange(1, 65535);

    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    QHBoxLayout *hostLayout = new QHBoxLayout;
    hostLayout->addWidget(hostLabel);
    hostLayout->addWidget(hostLineEdit);

    QHBoxLayout *portLayout = new QHBoxLayout;
    portLayout->addWidget(portLabel);
    portLayout->addWidget(portSpinBox);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hostLayout);
    mainLayout->addLayout(portLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    readFile();

    hostLineEdit->setText(host);
    portSpinBox->setValue(port);

    connect(okButton, &QPushButton::clicked, this, &SettingsDialog::onOkButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &SettingsDialog::onCancelButtonClicked);
}

void SettingsDialog::readFile()
{
    QFile cfg(defaultPath);
    if (cfg.open(QIODevice::ReadOnly)){
        QTextStream in(&cfg);
        QJsonDocument doc = QJsonDocument::fromJson(in.readAll().toUtf8());
        QJsonObject obj = doc.object();
        if (obj["host"].isString() && obj["port"].isDouble()){
            host =obj["host"].toString();
            port = obj["port"].toInt();
        }
        cfg.close();
    }
}

void SettingsDialog::writeFile()
{
    QFile cfg(defaultPath);
    if (cfg.open(QIODevice::WriteOnly)){
        QTextStream out(&cfg);
        QJsonObject obj;

        obj["host"] = host;
        obj["port"] = (qint64)port;

        out << QString::fromUtf8(QJsonDocument(obj).toJson());
        cfg.close();
    }
}

SettingsDialog::~SettingsDialog() {}

QPair<QString, int> SettingsDialog::getSettings() const {
    return QPair<QString, int>(hostLineEdit->text(), portSpinBox->value());
}

void SettingsDialog::onOkButtonClicked() {

    host = hostLineEdit->text();
    port = portSpinBox->value();

    writeFile();

    accept();
}


void SettingsDialog::onCancelButtonClicked() {
    reject();
}
