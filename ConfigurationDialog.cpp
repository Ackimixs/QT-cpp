#include "ConfigurationDialog.h"

ConfigurationDialog::ConfigurationDialog() : QDialog() {
    this->ipAddress = new LabeledTextField();
    this->password = new LabeledTextField();
    this->user = new LabeledTextField();

    this->layout = new QVBoxLayout();

    this->ipAddress->setText("Ip Address");
    this->password->setText("Password");
    this->user->setText("User");

    this->layout->addWidget(this->ipAddress);
    this->layout->addWidget(this->password);
    this->layout->addWidget(this->user);

    this->setLayout(this->layout);

    this->setMinimumSize(500, 180);
}