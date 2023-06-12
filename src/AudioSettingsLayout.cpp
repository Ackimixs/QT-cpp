#include "AudioSettingsLayout.h"

AudioSettingsLayout::AudioSettingsLayout(QString label, QString settingName) : QHBoxLayout(), settingName(settingName) {
    this->audioLabel = new QLabel(label);
    this->audioSlider = new QSlider(Qt::Horizontal);

    this->audioSlider->setRange(0, 100);

    this->addWidget(this->audioLabel);
    this->addWidget(this->audioSlider);

    connect(this->audioSlider, SIGNAL(valueChanged(int)), this, SLOT(changeAudioLevel(int)));
}

void AudioSettingsLayout::setAudioLevel(int level) {
    this->audioSlider->setValue(level);
}

void AudioSettingsLayout::changeAudioLevel(int level) {
    qInfo() << settingName << " : " << level;
    SettingsManager::getInstance().setValue(this->settingName, level);
}