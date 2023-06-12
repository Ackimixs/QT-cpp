#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    this->layout = new QVBoxLayout(this);

    this->mainMusicVolume = new AudioSettingsLayout("Main music", "mainMusicLevel");
    this->gameMusique = new AudioSettingsLayout("Game music", "gameMusicLevel");
    this->effectMusique = new AudioSettingsLayout("Effect music", "effectMusicLevel");

    this->mainMusicVolume->setAudioLevel(SettingsManager::getInstance().value("mainMusicLevel").toInt());
    this->gameMusique->setAudioLevel(SettingsManager::getInstance().value("gameMusicLevel").toInt());
    this->effectMusique->setAudioLevel(SettingsManager::getInstance().value("effectMusicLevel").toInt());

    layout->addLayout(mainMusicVolume);
    layout->addLayout(gameMusique);
    layout->addLayout(effectMusique);

    // Create labels and line edits for keyboard mappings
    this->forwardKey = new MappingLayout("forward");
    this->rightKey = new MappingLayout("right");
    this->backwardKey = new MappingLayout("backward");
    this->leftKey = new MappingLayout("left");
    this->spaceKey = new MappingLayout("space");
    this->restartKey = new MappingLayout("restart");

    layout->addLayout(forwardKey);
    layout->addLayout(rightKey);
    layout->addLayout(backwardKey);
    layout->addLayout(leftKey);
    layout->addLayout(spaceKey);
    layout->addLayout(restartKey);

    // Create a save button
    QPushButton* saveButton = new QPushButton("Save", this);
    layout->addWidget(saveButton);

    connect(saveButton, SIGNAL(pressed()), this, SLOT(saveSettings()));
}

void SettingsDialog::saveSettings() {
    emit settingsSaved();
    close();
}