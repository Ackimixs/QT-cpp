#include <QHBoxLayout>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    planeViews = QVector<QGraphicsView*>();

    this->mainScene = new MainScene();

    mainView = new QGraphicsView();
    mainView->setScene(mainScene);
    mainView->scale(0.2, 0.2);

    this->setCentralWidget(mainView);
    this->setWindowTitle("Main view");
    this->resize(900, 300);

    for (int i = 0; i < 3; i++) {
        planeViews.append(new QGraphicsView());
        planeViews[i]->setWindowTitle(QString("plane %1").arg(i + 1));
        planeViews[i]->resize(300, 300);
        planeViews[i]->setScene(this->mainScene);
        planeViews[i]->show();
    }
}