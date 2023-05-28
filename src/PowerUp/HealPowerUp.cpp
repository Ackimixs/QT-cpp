#include "HealPowerUp.h"

HealPowerUp::HealPowerUp() : PowerUp() {
    QPixmap base = this->pixmap();
    QPixmap healPixmap(":/assets/img/powerup/heal.png");
    this->setPixmap(Utils::addPixmapOnTop(base, healPixmap));

    this->type = PowerUp::Heal;
}