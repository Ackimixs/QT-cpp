#include <QApplication>
#include <QPushButton>

#include "MainWindow.h"
#include "ex2.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    /*MainWindow m;

    m.show();*/

    ex2 m;

    m.show();
    return QApplication::exec();
}
