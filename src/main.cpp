#include <QApplication>
#include "MainWindow.h"
#include "Logger.h"

int main(int argc, char *argv[]) {
    Logger::isDevMode = true;
    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
