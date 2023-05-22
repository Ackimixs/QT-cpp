#include <QApplication>
#include "SQLClientWindow.h"
#include "ConfigurationDialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SQLClientWindow w;
    ConfigurationDialog cg;

    w.show();
    cg.show();

    return QApplication::exec();
}
