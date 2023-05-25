#include "Explosion.h"

Explosion::Explosion(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent) {

    Logger::log({"Explosion"}, Logger::Create, "create an explosion", true);

    QPixmap anim(":/assets/img/Explosion/explosion_01.png");
    this->setPixmap(anim.scaled(70, 70, Qt::KeepAspectRatio));
    this->state = 1;

    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(75);
}

Explosion::~Explosion() {
    Logger::log({"Explosion"}, Logger::Delete, "deleted an explosion", true);
    this->timer->stop();
    delete this->timer;
}

void Explosion::update() {
    if (this->state >= 9) {
        delete this;
        return;
    }
    else {
        this->state++;
        this->setPixmap(QPixmap(":/assets/img/Explosion/explosion_0" + QString::number(this->state) + ".png").scaled(70, 70, Qt::KeepAspectRatio));
    }
}