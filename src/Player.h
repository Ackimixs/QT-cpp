#ifndef CPP_QT_TPMINIPROJET_PLAYER_H
#define CPP_QT_TPMINIPROJET_PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>
#include <QColor>

#include "Logger.h"
#include "Bullet.h"
#include "PowerUp.h"

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int speed;

    QSet<int> pressedKeys;

    qreal lifePoint;

    qreal score;

    bool gameOver;

    QTime timeUntilNewShoot;

    qreal timeBetween2Shoot;

    bool isRateOfFireUp;

    QTime timeUntilRateOfFire;

    bool isSniperUp;

    QTime timeUntilSniper;

    QTimer* timer;

public:
    Player(QString imageFileName);

    virtual ~Player();

    void keyPressEvent(QKeyEvent * event) override;

    void keyReleaseEvent(QKeyEvent * event) override;

    int getSpeed() const { return this->speed; };

    void removeOneLife();

    void reset();

    QGraphicsTextItem* lifePointText;

    QGraphicsTextItem* scoreText;

    void addLifePoint();

    qreal getScore() const { return this->score; };

public slots:
    void addPoint();

    void update();

signals:
    void gameOverFunc();

    void gameRestartSignal();

};


#endif //CPP_QT_TPMINIPROJET_PLAYER_H
