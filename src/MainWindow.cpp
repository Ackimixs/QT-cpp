#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    this->mainScene = new MyScene;

    this->mainView = new QGraphicsView(this);
    this->mainView->setScene(mainScene);

    this->mainView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->mainView->setResizeAnchor(QGraphicsView::NoAnchor);

    QImage img(":/assets/img/background/sky_background_green_hills.png");
    this->mainScene->setBackgroundBrush(img);

    this->setCentralWidget(mainView);
    this->setWindowTitle("My main window");
    this->resize(400, 800);

    this->mainScene->setSceneRect(this->geometry());

    this->resize(420, 840);

    this->mainScene->resizePlane(400, 800);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* actionHelp = new QAction(tr("&About"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    helpMenu->addAction(actionHelp);

    this->db = new Database();

}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;
    msgBox.setText("A small QT/C++ projet...");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}
