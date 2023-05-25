#include "RateOfFirePowerUp.h"

RateOfFirePowerUp::RateOfFirePowerUp() : PowerUp() {
    QPixmap base = this->pixmap();
    QPixmap rateOfFirePixmap(":/assets/img/powerup/torpedo.png");
    this->setPixmap(Utils::addPixmapOnTop(base, rateOfFirePixmap));

    this->type = PowerUp::RateOfFire;
}

PowerUp::Type RateOfFirePowerUp::getPowerUp() {
    return this->type;
}