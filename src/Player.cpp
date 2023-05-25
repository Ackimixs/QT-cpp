#include "Player.h"

Player::Player(QString imageFileName) : QObject(), QGraphicsPixmapItem(), lifePoint(3), score(0), speed(10), gameOver(false) {
    QPixmap img(imageFileName);
    this->setPixmap(img.scaled(105, 105, Qt::KeepAspectRatio));
    Logger::log({"Player"}, Logger::Create, "Player created", true);
    this->lifePointText = new QGraphicsTextItem();
    this->lifePointText->setPlainText("Life : " + QString::number(this->lifePoint));
    this->scoreText = new QGraphicsTextItem();
    this->scoreText->setPlainText("Score : " + QString::number(this->score));

    this->scoreText->setDefaultTextColor(Qt::black);
    this->lifePointText->setDefaultTextColor(Qt::black);

    this->timeUntilNewShoot = QTime::currentTime();

    this->timeBetween2Shoot = 1;

    this->isRateOfFireUp = false;

    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(100);

}

Player::~Player() {
    Logger::log({"Player"}, Logger::Delete, "Player deleted", true);
}

void Player::keyPressEvent(QKeyEvent *event) {

    if (gameOver) {
        pressedKeys.clear();
        return;
    }

    //Logger::log({"Player"}, "debug", "Key pressed -> player pos : (" + QString::number(this->x()) + "," + QString::number(this->y()) + ")", true);

    //Logger::log({"Player"}, "debug", QString::number(this->scene()->width()) + " " + QString::number(this->x() + this->pixmap().width()), true);

    pressedKeys.insert(event->key());

    if (pressedKeys.contains(Qt::Key_Down) && (this->y() + this->pixmap().height()) < this->scene()->height()) {
        this->setPos(this->x(), this->y() + this->speed);
    }
    if (pressedKeys.contains(Qt::Key_Up) && this->x() > 0) {
        this->setPos(this->x(), this->y() - this->speed);
    }
    if (pressedKeys.contains(Qt::Key_Left) && this->x() > 0) {
        this->setPos(this->x() - this->speed, this->y());
    }
    if (pressedKeys.contains(Qt::Key_Right) && (this->x() + this->pixmap().width()) < this->scene()->width()) {
        this->setPos(this->x() + this->speed, this->y());
    }


    if (pressedKeys.contains(Qt::Key_Space)) {

        if (QTime::currentTime() > this->timeUntilNewShoot) {
            this->timeUntilNewShoot = QTime::currentTime().addSecs(this->timeBetween2Shoot);

            Bullet* bullet = new Bullet(":/assets/img/bullet/torpedo.png", Bullet::playerBullet, -90, 20);
            Bullet* bulletLeft = new Bullet(":/assets/img/bullet/torpedo.png", Bullet::playerBullet, -95, 20);
            Bullet* bulletRight = new Bullet(":/assets/img/bullet/torpedo.png", Bullet::playerBullet, -85, 20);
            this->scene()->addItem(bullet);
            this->scene()->addItem(bulletLeft);
            this->scene()->addItem(bulletRight);
            bulletLeft->setPos(this->x() - (bullet->pixmap().height() / 2) + 3 * (this->pixmap().width() / 8), this->y());
            bullet->setPos((this->x() - (bulletLeft->pixmap().height() / 2)) + 2 * (this->pixmap().width() / 4), this->y());
            bulletRight->setPos((this->x() - (bulletRight->pixmap().height() / 2)) + 5 * (this->pixmap().width() / 8), this->y());

            connect(bullet, SIGNAL(collisionWithEnemiesSignal()), this, SLOT(addPoint()));
            connect(bulletLeft, SIGNAL(collisionWithEnemiesSignal()), this, SLOT(addPoint()));
            connect(bulletRight, SIGNAL(collisionWithEnemiesSignal()), this, SLOT(addPoint()));
        }
    }

    if (pressedKeys.contains(Qt::Key_R)) {
        Logger::log({"Game"}, Logger::Debug, "Player ask for restart", true);
        emit gameRestartSignal();
    }

    QGraphicsPixmapItem::keyPressEvent(event);
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    this->pressedKeys.remove(event->key());
    QGraphicsPixmapItem::keyReleaseEvent(event);
}

void Player::removeOneLife() {
    if (this->lifePoint == 0) {
        this->gameOver = true;
        emit gameOverFunc();
        return;
    } else {
        this->lifePoint -= 1;
    }
    this->lifePointText->setPlainText("Life : " + QString::number(this->lifePoint));
}

void Player::addPoint() {
    this->score += 1;
    this->scoreText->setPlainText("Score : " + QString::number(this->score));
}

void Player::reset() {
    this->lifePoint = 0;
    this->score = 0;
    this->lifePointText->setPlainText("Life : " + QString::number(this->lifePoint));
    this->scoreText->setPlainText("Score :" + QString::number(this->score));
    this->gameOver = false;
}

void Player::update() {

    if (isRateOfFireUp) {
        if (QTime::currentTime() > timeUntilRateOfFire) {
            this->isRateOfFireUp = false;
            this->timeBetween2Shoot = 1;
        }
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        PowerUp* powerUp = dynamic_cast<PowerUp*>(colliding_items[i]);
        if (powerUp) {
            PowerUp::Type type = powerUp->getPowerUp();
            if (type == PowerUp::Heal) {
                this->addLifePoint();
                delete powerUp;
            } else if (type == PowerUp::RateOfFire) {
                this->timeBetween2Shoot = 0;
                this->isRateOfFireUp = true;
                this->timeUntilRateOfFire = QTime::currentTime().addSecs(5);
                delete powerUp;
            }
        }
    }
}

void Player::addLifePoint() {
    this->lifePoint++;
    this->lifePointText->setPlainText("Life : " + QString::number(this->lifePoint));
}

//TODO faire un power Up sniper qui passe a travers