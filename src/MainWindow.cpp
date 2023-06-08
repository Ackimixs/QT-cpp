#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    this->mainScene = new MyScene();

    this->mainView = new QGraphicsView(this);
    this->mainView->setScene(mainScene);

    this->mainView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->mainView->setResizeAnchor(QGraphicsView::NoAnchor);

    this->mainScene->setSceneRect(0, 0, 400, 800);

    this->actualCut = 1;
    this->maxCut = 256;
    this->backgroundImg = new QImage(":/assets/img/background/backgroundTest.png");

    this->mainScene->setBackgroundBrush(Utils::cutImage(*this->backgroundImg, 800, this->maxCut, this->actualCut).scaled(420, 840, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    this->setCentralWidget(mainView);
    this->setWindowTitle("Cyber space");

    this->setFixedSize(420, 840);

    this->mainScene->resizePlane(400, 800);

    this->mainScene->setupGameOverScreen();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* actionHelp = new QAction(tr("&About"), this);
    QAction* restartHelp = new QAction(tr("&Restart"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    connect(restartHelp, SIGNAL(triggered()), this, SLOT(slot_restartMenu()));
    helpMenu->addAction(actionHelp);
    helpMenu->addAction(restartHelp);

    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));

    connect(this->mainScene, SIGNAL(quitGameSignal()), this, SLOT(close()));
    connect(this->mainScene, SIGNAL(startGameSignal()), this, SLOT(startGame()));
}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;

    QString osName = QSysInfo::prettyProductName();
    QString osVersion = QSysInfo::productVersion();
    QString architecture = QSysInfo::currentCpuArchitecture();

    msgBox.setWindowTitle("About");
    msgBox.setText("Qt version" + QString(QT_VERSION_STR) + "\n" +
                   "Operating System: " + osName + "\n" +
                   "Operating System Version: " + osVersion + "\n" +
                   "Architecture: " + architecture + "\n" +
                   "Kernel : " + QSysInfo::kernelType() + " " + QSysInfo::kernelVersion() + "\n" +
                   "Build : " + QSysInfo::buildAbi() + "\n" +
                   "git repo : https://github.com/ackimixs/QT-cpp/tree/miniProjet");

    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::slot_settingsMenu() {
    SettingsDialog settingsDialog(this);
    settingsDialog.setWindowTitle("Settings");
    settingsDialog.exec();
}

void MainWindow::update() {
    if (this->actualCut > this->maxCut) {
        this->actualCut = 0;
    }

    this->mainScene->setBackgroundBrush(Utils::cutImage(*this->backgroundImg, 800, this->maxCut, this->actualCut).scaled(420, 840, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    this->actualCut++;
}

void MainWindow::startGame() {
    this->timer->start(50);
}

void MainWindow::slot_restartMenu() {
    this->restartDialog = new QDialog(this);
    this->restartDialog->setWindowTitle("Restart");
    this->restartDialog->setModal(true);
    QVBoxLayout* dialogLayout = new QVBoxLayout(this->restartDialog);
    QLabel* label = new QLabel("Are you sure you want to restart the game ?");
    this->difficulty = new QComboBox();
    this->difficulty->addItem("Easy");
    this->difficulty->addItem("Medium");
    this->difficulty->addItem("Hard");
    this->difficulty->addItem("Impossible");
    this->difficulty->addItem("Are u ok ?");
    this->difficulty->addItem("Power Up");
    label->setAlignment(Qt::AlignCenter);
    dialogLayout->addWidget(label);
    dialogLayout->addWidget(this->difficulty);
    QPushButton* okButton = new QPushButton("restart");
    connect(okButton, SIGNAL(pressed()), this, SLOT(restartSlots()));

    dialogLayout->addWidget(okButton);
    this->restartDialog->exec();
}

void MainWindow::restartSlots() {
    this->mainScene->restartSlots(this->difficulty->currentIndex());
    this->restartDialog->close();
}