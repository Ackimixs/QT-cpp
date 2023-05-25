#include "PowerUp.h"

PowerUp::PowerUp() : QObject(), QGraphicsPixmapItem() {

    Logger::log({"PowerUp"}, Logger::Create, "Create a base PowerUp", true);

    QPixmap base = Utils::addTransparencyToPixmap(QPixmap(":/assets/img/powerup/pearl_blue.png"));

    this->setPixmap(base);
    this->type = PowerUp::Null;

    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(40);
}

PowerUp::~PowerUp() {
    Logger::log({"PowerUp"}, Logger::Delete, "Delete a base PowerUp", true);
    this->timer->stop();
    delete this->timer;
}

PowerUp::Type PowerUp::getPowerUp() {
    return this->type;
}

void PowerUp::update() {
    if (this->y() > (this->scene()->height() + this->pixmap().height())) {
        delete this;
    } else {
        this->setPos(this->x() + Utils::randInt(-1, 2), this->y() + 5);
    }
}
