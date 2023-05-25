#ifndef CPP_QT_TPMINIPROJET_HEALPOWERUP_H
#define CPP_QT_TPMINIPROJET_HEALPOWERUP_H

#include "../PowerUp.h"

class HealPowerUp : public PowerUp {
public:
    HealPowerUp();

    PowerUp::Type getPowerUp() override;
};


#endif //CPP_QT_TPMINIPROJET_HEALPOWERUP_H
