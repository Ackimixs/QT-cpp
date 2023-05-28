#include "SniperPowerUp.h"

SniperPowerUp::SniperPowerUp() {
    QPixmap base = this->pixmap();
    QPixmap sniperPixmap(":/assets/img/powerup/sniper.png");
    this->setPixmap(Utils::addPixmapOnTop(base, sniperPixmap));

    this->type = PowerUp::Sniper;
}