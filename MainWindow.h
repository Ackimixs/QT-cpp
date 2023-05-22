#ifndef TP3_MAINWINDOW_H
#define TP3_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QSlider>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

private:
    QSlider* slider;
    QVBoxLayout* layout;
    QProgressBar* progressBar;
    QWidget* parent;

};


#endif //TP3_MAINWINDOW_H
