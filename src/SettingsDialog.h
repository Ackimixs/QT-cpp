#ifndef CPP_QT_MINIPROJET_SETTINGSDIALOG_H
#define CPP_QT_MINIPROJET_SETTINGSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "Database.h"
#include "MappingLayout.h"
#include "AudioSettingsLayout.h"
#include "settings.h"

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    SettingsDialog(QWidget* parent = nullptr);

private:
    QVBoxLayout* layout;

    AudioSettingsLayout* mainMusicVolume;
    AudioSettingsLayout* gameMusique;
    AudioSettingsLayout* effectMusique;


    MappingLayout* forwardKey;
    MappingLayout* rightKey;
    MappingLayout* backwardKey;
    MappingLayout* leftKey;
    MappingLayout* spaceKey;
    MappingLayout* restartKey;

public slots:
    void saveSettings();

signals:
    void settingsSaved();
};


#endif //CPP_QT_MINIPROJET_SETTINGSDIALOG_H
