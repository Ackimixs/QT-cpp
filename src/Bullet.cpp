#include "Bullet.h"

Bullet::Bullet(QString filename, Type type, qreal angle, qreal speed, bool isSniper, QGraphicsPixmapItem* parent) : QObject(), QGraphicsPixmapItem(parent), angle(angle), speed(speed), type(type), gameOver(false), isSniper(isSniper) {
    //Logger::log({"Bullet"}, Logger::Create, "Bullet create", true);
    QPixmap img(filename);

    if (type == playerBullet) {
        this->setPixmap(img.scaled(40, 40, Qt::KeepAspectRatio));
    } else if (type == enemieBullet) {
        this->setPixmap(img.scaled(20, 20, Qt::KeepAspectRatio));
    }

    this->setRotation(angle);

    this->bulletTimer = new QTimer();
    connect(this->bulletTimer, SIGNAL(timeout()), this, SLOT(move()));

    this->bulletTimer->start(50);
}

Bullet::~Bullet() {
    //Logger::log({"Bullet"}, Logger::Delete, "Bullet deleted", true);
    this->bulletTimer->stop();
    delete this->bulletTimer;
}

void Bullet::move() {

    if (this->gameOver) {
        this->bulletTimer->stop();
        return;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemies) && this->type == playerBullet) {
            Logger::log({"Collision"}, Logger::Debug, "Bullet touch enemies", true);

            Explosion* exp = new Explosion();
            scene()->addItem(exp);
            exp->setPos(colliding_items[i]->x() - colliding_items[i]->boundingRect().width(), colliding_items[i]->y() - colliding_items[i]->boundingRect().height());

            int nb = Utils::randInt(1, 21);

            if (nb == 1) {
                HealPowerUp* healPowerUp = new HealPowerUp();
                scene()->addItem(healPowerUp);
                healPowerUp->setPos(colliding_items[i]->x() - colliding_items[i]->boundingRect().width(), colliding_items[i]->y() - colliding_items[i]->boundingRect().height());
            } else if (nb == 2) {
                RateOfFirePowerUp* rateOfFirePowerUp = new RateOfFirePowerUp();
                scene()->addItem(rateOfFirePowerUp);
                rateOfFirePowerUp->setPos(colliding_items[i]->x() - colliding_items[i]->boundingRect().width(), colliding_items[i]->y() - colliding_items[i]->boundingRect().height());
            } else if (nb == 3) {
                SniperPowerUp* sniperPowerUp = new SniperPowerUp();
                scene()->addItem(sniperPowerUp);
                sniperPowerUp->setPos(colliding_items[i]->x() - colliding_items[i]->boundingRect().width(), colliding_items[i]->y() - colliding_items[i]->boundingRect().height());
            }
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            emit collisionWithEnemiesSignal();
            if (!this->isSniper) {
                scene()->removeItem(this);
                delete this;
            }
            return;
        } else if (typeid(*colliding_items[i]) == typeid(Player) && this->type == enemieBullet) {
            Logger::log({"Collision"}, Logger::Debug, "Bullet touch player", true);
            scene()->removeItem(this);
            emit this->collisionWithPlayerSignal();
            delete this;
            return;
        } else if (typeid(*(colliding_items[i])) == typeid(Bullet) && this->type == enemieBullet) {
            Bullet* otherBullet = dynamic_cast<Bullet*>(colliding_items[i]);
            Logger::log({"Collision"}, Logger::Debug, "bullet touch an other bullet", true);
            if (!otherBullet->isSniper) {
                scene()->removeItem(colliding_items[i]);
                delete colliding_items[i];
            }
            scene()->removeItem(this);
            delete this;
            return;
        }
    }


    qreal dx = this->speed * qCos(qDegreesToRadians(angle));
    qreal dy = this->speed * qSin(qDegreesToRadians(angle));

    QPointF currentPosition = this->pos();

    qreal decalX = Utils::randInt(-2, 2);

    QPointF newPosition = currentPosition + QPointF(dx + decalX, dy);

    this->setPos(newPosition);

    if (pos().y() < 0 || pos().y() > this->scene()->height()) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void Bullet::gameOverSlot() {
    this->gameOver = true;
}