#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    this->layout = new QVBoxLayout(this);

    QList<QMap<QString, QString>> res = Database::query("SELECT * FROM keymappings");

    // Create labels and line edits for keyboard mappings
    this->forwardKey = new MappingLayout("forward");
    this->rightKey = new MappingLayout("right");
    this->backwardKey = new MappingLayout("backward");
    this->leftKey = new MappingLayout("left");

    for (int i = 0; i < res.count(); i++) {
        if (res[i].value("context") == "forward") {
            this->forwardKey->setInputText(res[i].value("key"));
        } else if (res[i].value("context") == "right") {
            this->rightKey->setInputText(res[i].value("key"));
        } else if (res[i].value("context") == "backward") {
            this->backwardKey->setInputText(res[i].value("key"));
        } else if (res[i].value("context") == "left") {
            this->leftKey->setInputText(res[i].value("key"));
        }
    }

    layout->addLayout(forwardKey);
    layout->addLayout(rightKey);
    layout->addLayout(backwardKey);
    layout->addLayout(leftKey);

    // Create a save button
    QPushButton* saveButton = new QPushButton("Save", this);
    layout->addWidget(saveButton);

    connect(saveButton, &QPushButton::clicked, this, &SettingsDialog::saveSettings);
}

void SettingsDialog::saveSettings() {
    QString forward = forwardKey->getText();
    QString right = rightKey->getText();
    QString backward = backwardKey->getText();
    QString left = leftKey->getText();

    qInfo() << forward << right << backward << left;

    close();
}