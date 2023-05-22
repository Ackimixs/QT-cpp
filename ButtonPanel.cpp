#include "ButtonPanel.h"

ButtonPanel::ButtonPanel() : QWidget() {
    this->configure = new QPushButton("Configure");
    this->connect = new QPushButton("Connect");
    this->disconnect = new QPushButton("Disconnect");

    this->layout = new QHBoxLayout();

    this->layout->addWidget(this->configure);
    this->layout->addWidget(this->connect);
    this->layout->addWidget(this->disconnect);

    this->setLayout(this->layout);
}