#include "ex2.h"

ex2::ex2(QWidget* parent) : QMainWindow(parent) {

    this->nbClick = 0;

    this->parent = new QWidget(this);
    this->layout = new QVBoxLayout();
    this->buttonLayout = new QHBoxLayout();
    this->parent->setLayout(this->layout);
    this->layout->addLayout(this->buttonLayout);

    this->w = new MainWindow();

    this->textEdit = new QTextEdit();
    this->textEdit->setReadOnly(true);

    this->buttonOpenIHM = new QPushButton("open IHM");
    this->quitButton = new QPushButton("Quit");
    this->changeText = new QPushButton("Exemple");

    this->buttonLayout->addWidget(this->quitButton);
    this->buttonLayout->addWidget(this->changeText);
    this->buttonLayout->addWidget(this->buttonOpenIHM);
    this->layout->addWidget(this->textEdit);

    connect(this->quitButton, SIGNAL(pressed()), this, SLOT(close()));
    connect(this->changeText, SIGNAL(pressed()), this, SLOT(changeButtonText()));
    connect(this->buttonOpenIHM, SIGNAL(pressed()), this, SLOT(openIHM()));

    this->setCentralWidget(this->parent);

    connect(this, SIGNAL(signalValueChange(QString)), this , SLOT(slotsValueChange(QString)));
}

void ex2::changeButtonText() {
    this->nbClick++;
    
    emit signalValueChange(this->changeText->text() + QString(" %1").arg(this->nbClick));
}

void ex2::openIHM() {
    this->w->show();
}

void ex2::slotsValueChange(QString s) {
    this->textEdit->append(s);
}