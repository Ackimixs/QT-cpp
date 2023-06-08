#ifndef CPP_QT_TPMINIPROJET_BULLET_H
#define CPP_QT_TPMINIPROJET_BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>

#include "utils.h"
#include "Enemies.h"
#include "Player.h"
#include "Explosion.h"
#include "PowerUp/HealPowerUp.h"
#include "PowerUp/RateOfFirePowerUp.h"
#include "PowerUp/SniperPowerUp.h"

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum Type {
        enemieBullet,
        playerBullet
    };

    Bullet(QString filename, Type type = playerBullet, qreal angle = -90, qreal speed = 10, bool isSniper = false, int difficulty = 1, QGraphicsPixmapItem* parent = nullptr);

    ~Bullet();

private:
    QTimer* bulletTimer;
    qreal angle;
    qreal speed;
    qreal type;
    bool gameOver;
    bool isSniper;
    int difficulty;

public slots:
    void move();

    void gameOverSlot();

signals:
    void collisionWithPlayerSignal();

    void collisionWithEnemiesSignal();
};


#endif //CPP_QT_TPMINIPROJET_BULLET_H
