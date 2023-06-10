#include "keyPressedDialogRecorder.h"

keyPressedDialogRecorder::keyPressedDialogRecorder(QWidget *parent) : QDialog(parent) {
    this->label = new QLabel("Press a key", this);
    this->label->setAlignment(Qt::AlignCenter);
    this->label->setStyleSheet("font-size: 20px;");
    this->setWindowTitle("Press a key");
}

void keyPressedDialogRecorder::keyPressEvent(QKeyEvent *event) {
    emit keyChanged(event->key());
    close();
}
