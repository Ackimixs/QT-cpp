#ifndef TP3_EX2_H
#define TP3_EX2_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTextEdit>

#include "MainWindow.h"

class ex2 : public QMainWindow {
    Q_OBJECT
public:
    ex2(QWidget* parent = nullptr);

private:
    QPushButton* changeText;
    QPushButton* quitButton;
    QPushButton* buttonOpenIHM;
    QVBoxLayout* layout;
    QHBoxLayout* buttonLayout;
    QWidget* parent;
    QTextEdit* textEdit;

    int nbClick;

    MainWindow* w;

private slots:
    void changeButtonText();
    void openIHM();
    void slotsValueChange(QString s);

    signals:
    void signalValueChange(QString s);
};


#endif //TP3_EX2_H
