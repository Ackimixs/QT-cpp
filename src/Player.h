#ifndef CPP_QT_TPMINIPROJET_PLAYER_H
#define CPP_QT_TPMINIPROJET_PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "Logger.h"
#include "Bullet.h"
#include "PowerUp.h"
#include "settings.h"

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int speed;

    QSet<int> pressedKeys;

    qreal lifePoint;

    qreal score;

    bool gameOver;

    bool isGameStarted;

    QTime timeUntilNewShoot;

    qreal timeBetween2Shoot;

    bool isRateOfFireUp;

    QTime timeUntilRateOfFire;

    bool isSniperUp;

    QTime timeUntilSniper;

    QTimer* timer;

    int difficulty;

public:
    Player(QString imageFileName, QGraphicsItem* parent = nullptr);

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

    void startGame();

    void setDifficulty(int difficulty);
public slots:
    void addPoint();

    void update();

signals:
    void gameOverFunc();

    void gameRestartSignal();

};


#endif //CPP_QT_TPMINIPROJET_PLAYER_H
