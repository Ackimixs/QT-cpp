#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MainScene.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QVector>


class MainWindow : public QMainWindow
{
    Q_OBJECT

private :
    MainScene* mainScene;

    QVector<QGraphicsView*> planeViews;
    QGraphicsView* mainView;


public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() {};

};

#endif // MAINWINDOW_H
