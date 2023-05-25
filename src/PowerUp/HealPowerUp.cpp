#include "HealPowerUp.h"

HealPowerUp::HealPowerUp() : PowerUp() {
    QPixmap base = this->pixmap();
    QPixmap rateOfFirePixmap(":/assets/img/powerup/heal.png");
    this->setPixmap(Utils::addPixmapOnTop(base, rateOfFirePixmap));

    this->type = PowerUp::Heal;
}

PowerUp::Type HealPowerUp::getPowerUp() {
    return this->type;
}