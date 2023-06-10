#ifndef CPP_QT_MINIPROJET_KEYPRESSEDDIALOGRECORDER_H
#define CPP_QT_MINIPROJET_KEYPRESSEDDIALOGRECORDER_H

#include <QDialog>
#include <QKeyEvent>
#include <QLabel>

#include "settings.h"

class keyPressedDialogRecorder : public QDialog {
    Q_OBJECT
public:
    keyPressedDialogRecorder(QWidget* parent = nullptr);
protected:
    QLabel* label;
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void keyChanged(int key);
};


#endif //CPP_QT_MINIPROJET_KEYPRESSEDDIALOGRECORDER_H
