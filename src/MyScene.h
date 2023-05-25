#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsView>
#include <QKeyEvent>

#include "Player.h"
#include "Enemies.h"

class MyScene : public QGraphicsScene {
    Q_OBJECT

public:
    MyScene(QObject* parent = nullptr);
    virtual ~MyScene();

    void resizePlane(qreal sceneWidth, qreal sceneHeight);

private:

    QTimer* timer;
    Player* player;
    bool gameOver;

public slots:

    void handlePlayerCollision();

    void update();

    void gameOverFunc();

    void restartSlots();

signals:

    void gameOverSignal();
};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
