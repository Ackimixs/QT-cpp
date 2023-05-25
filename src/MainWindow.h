#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QDebug>

#include "MyScene.h"
#include "Player.h"
#include "Database.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    MyScene* mainScene;
    QGraphicsView* mainView;
    QMenu* helpMenu;
    Database* db;

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:
    void slot_aboutMenu();

};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H
