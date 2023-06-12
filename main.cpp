#include <QApplication>

#include "src/MainWindow.h"
#include "src/Database.h"
#include "src/settings.h"

void settingUp() {
    QSettings& settings = SettingsManager::getInstance();
    if (!settings.contains("forward")) {
        settings.setValue("forward", Qt::Key_Z);
    }
    if (!settings.contains("right")) {
        settings.setValue("right", Qt::Key_D);
    }
    if (!settings.contains("backward")) {
        settings.setValue("backward", Qt::Key_S);
    }
    if (!settings.contains("left")) {
        settings.setValue("left", Qt::Key_Q);
    }
    if (!settings.contains("space")) {
        settings.setValue("space", Qt::Key_Space);
    }
    if (!settings.contains("restart")) {
        settings.setValue("restart", Qt::Key_R);
    }
    if (!settings.contains("money")) {
        settings.setValue("money", 0);
    }
    if (!settings.contains("selectedShip")) {
        settings.setValue("selectedShip", "1");
    }
    if (!settings.contains("hasShip1")) {
        settings.setValue("hasShip1", true);
    }
    if (!settings.contains("hasShip2")) {
        settings.setValue("hasShip2", false);
    }
    if (!settings.contains("hasShip3")) {
        settings.setValue("hasShip3", false);
    }
    if (!settings.contains("hasShip4")) {
        settings.setValue("hasShip4", false);
    }
    if (!settings.contains("hasShip5")) {
        settings.setValue("hasShip5", false);
    }
    if (!settings.contains("hasShip6")) {
        settings.setValue("hasShip6", false);
    }
    if (!settings.contains("hasShip7")) {
        settings.setValue("hasShip7", false);
    }
    if (!settings.contains("hasShip8")) {
        settings.setValue("hasShip8", false);
    }
    if (!settings.contains("hasShip9")) {
        settings.setValue("hasShip9", false);
    }
    if (!settings.contains("mainMusicLevel")) {
        settings.setValue("mainMusicLevel", 50.0);
    }
    if (!settings.contains("gameMusicLevel")) {
        settings.setValue("gameMusicLevel", 50.0);
    }
    if (!settings.contains("effectMusicLevel")) {
        settings.setValue("effectMusicLevel", 50.0);
    }
}

int main(int argc, char *argv[]) {
    Logger::isDevMode = true;
    settingUp();
    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}