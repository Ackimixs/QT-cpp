#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    this->db = new Database();

    this->mainScene = new MyScene(db);

    this->mainView = new QGraphicsView(this);
    this->mainView->setScene(mainScene);

    this->mainView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->mainView->setResizeAnchor(QGraphicsView::NoAnchor);

    this->mainScene->setSceneRect(0, 0, 400, 800);

    QImage img = Utils::cutImage(":/assets/img/background/backgroundTest.png", 800, 128, 1);

    this->mainScene->setBackgroundBrush(img.scaled(420, 840, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    this->setCentralWidget(mainView);
    this->setWindowTitle("My main window");

    this->setFixedSize(420, 840);

    this->mainScene->resizePlane(400, 800);

    this->mainScene->setupGameOverScreen();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* actionHelp = new QAction(tr("&About"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    helpMenu->addAction(actionHelp);

    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(50);
}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;
    msgBox.setText("A small QT/C++ projet...");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::update() {
    if (this->actualCut > 256) {
        this->actualCut = 0;
    }

    QImage img = Utils::cutImage(":/assets/img/background/backgroundTest.png", 800, 256, actualCut);

    this->mainScene->setBackgroundBrush(img.scaled(420, 840, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    this->actualCut++;
}