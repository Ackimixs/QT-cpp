#include "MappingLayout.h"

MappingLayout::MappingLayout(QString label) : QHBoxLayout() {
    this->mappingLineEdit1 = new QLineEdit();
    this->mappingLabel1 = new QLabel(label);
    this->addWidget(this->mappingLabel1);
    this->addWidget(this->mappingLineEdit1);
}

void MappingLayout::setText(QString text) {
    this->mappingLabel1->setText(text);
}

QString MappingLayout::getText() {
    return this->mappingLineEdit1->text();
}

void MappingLayout::setInputText(QString text) {
    this->mappingLineEdit1->setText(text);
}