#ifndef CPP_QT_MINIPROJET_AUDIOSETTINGSLAYOUT_H
#define CPP_QT_MINIPROJET_AUDIOSETTINGSLAYOUT_H

#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>

#include "settings.h"

class AudioSettingsLayout : public QHBoxLayout {
    Q_OBJECT
public:
    AudioSettingsLayout(QString label, QString settingName);

    void setAudioLevel(int level);
public slots:
    void changeAudioLevel(int level);

signals:
    void audioLevelChanged();

protected:
    QLabel* audioLabel;
    QSlider* audioSlider;
    QString settingName;
};


#endif //CPP_QT_MINIPROJET_AUDIOSETTINGSLAYOUT_H
