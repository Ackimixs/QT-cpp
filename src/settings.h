#ifndef CPP_QT_MINIPROJET_SETTINGS_H
#define CPP_QT_MINIPROJET_SETTINGS_H

#pragma once

#include <QSettings>

class SettingsManager {
public:
    static QSettings& getInstance() {
        static QSettings settings("ackimixs", "cyberspace");
        return settings;
    }
};

#endif //CPP_QT_MINIPROJET_SETTINGS_H
