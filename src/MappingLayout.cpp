#include "MappingLayout.h"

MappingLayout::MappingLayout(QString label) : QHBoxLayout() {
    this->keySettings = label;
    this->mappingLabel1 = new QLabel(label);
    this->recordButton = new QPushButton("Record");
    if (SettingsManager::getInstance().contains(this->keySettings)) {
        QString keyStr =  QKeySequence(SettingsManager::getInstance().value(this->keySettings).toInt()).toString();
        this->recordButton->setText(keyStr);
    }
    this->dialog = new keyPressedDialogRecorder();

    this->addWidget(mappingLabel1);
    this->addWidget(recordButton);

    connect(this->recordButton, SIGNAL(pressed()), this, SLOT(recordKeyInfo()));
    connect(this->dialog, SIGNAL(keyChanged(int)), this, SLOT(keyChanged(int)));
}

void MappingLayout::recordKeyInfo() {
    this->dialog->exec();
}

void MappingLayout::keyChanged(int key) {
    this->recordButton->setText(QKeySequence(key).toString());

    QSettings& settings = SettingsManager::getInstance();

    settings.setValue(this->keySettings, key);

    Logger::log({"Key changed"}, Logger::Debug, "key " + this->keySettings + " changed to " + QKeySequence(key).toString(), true);
}