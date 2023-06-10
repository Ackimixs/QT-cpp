#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    this->layout = new QVBoxLayout(this);

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
    close();
}