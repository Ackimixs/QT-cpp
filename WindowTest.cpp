#include "WindowTest.h"
#include "Window.h"
#include <QApplication>

int test(int argc, char **argv) {
    QApplication app (argc, argv);

    Window w;
    w.show();

    return app.exec();
}