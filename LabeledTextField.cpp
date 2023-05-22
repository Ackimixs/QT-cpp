#include "LabeledTextField.h"

LabeledTextField::LabeledTextField() : QWidget() {

    this->layout = new QHBoxLayout();

    this->label = new QLabel();
    this->textEdit = new QTextEdit();

    this->layout->addWidget(this->label);
    this->layout->addWidget(this->textEdit);

    this->textEdit->setMaximumHeight(40);
    this->setLayout(this->layout);
}

void LabeledTextField::setText(QString s) {
    this->label->setText(s);
}