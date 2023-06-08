#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QDebug>
#include <QSysInfo>


#include "MyScene.h"
#include "Player.h"
#include "Database.h"
#include "SettingsDialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    MyScene* mainScene;
    QGraphicsView* mainView;
    QMenu* helpMenu;
    QTimer* timer;

    int actualCut;
    int maxCut;
    QImage* backgroundImg;

    QComboBox* difficulty;
    QDialog* restartDialog;

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:
    void slot_aboutMenu();

    void slot_settingsMenu();

    void slot_restartMenu();

    void update();

    void startGame();

    void restartSlots();
};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H
