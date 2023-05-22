#include "Window.h"

Window::Window(QWidget *parent) : QWidget(parent) {
    this->button = new QPushButton("test", this);

    this->setFixedSize(100, 50);
    this->button->setGeometry(10, 10, 80, 30);
    this->setWindowTitle("Ma super app");

}

