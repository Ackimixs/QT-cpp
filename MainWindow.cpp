#include "MainWindow.h"

MainWindow::MainWindow() : QMainWindow() {
    this->setWindowTitle("IHM");
    this->setMinimumSize(600, 400);

    this->parent = new QWidget();
    this->layout = new QVBoxLayout(this->parent);
    this->progressBar = new QProgressBar();
    this->progressBar->setRange(0, 100);
    this->progressBar->setValue(0);
    this->slider = new QSlider(Qt::Horizontal);

    this->parent->setLayout(this->layout);

    this->layout->addWidget(this->progressBar);
    this->layout->addWidget(this->slider);

    this->setCentralWidget(this->parent);

    connect(this->slider, SIGNAL(valueChanged(int)), this->progressBar, SLOT(setValue(int)));
}