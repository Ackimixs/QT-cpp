#ifndef CPP_QT_TPMINIPROJET_ENEMIES_H
#define CPP_QT_TPMINIPROJET_ENEMIES_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "Logger.h"
#include "utils.h"
#include "Bullet.h"

class Enemies : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemies(QString filename, QGraphicsPixmapItem* parent = nullptr);

    ~Enemies();

private:

    bool gameOver;

    QTimer* timer;

public slots:
    void move();
    void collisionWithPlayerSlot();
    void gameOverSlot();
signals:
    void collisionWithPlayerSignal();
    void gameOverSignal();
    void reachEndOfMapSignal();
};


#endif //CPP_QT_TPMINIPROJET_ENEMIES_H
