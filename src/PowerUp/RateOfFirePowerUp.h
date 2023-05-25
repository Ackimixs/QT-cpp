#ifndef CPP_QT_TPMINIPROJET_RATEOFFIREPOWERUP_H
#define CPP_QT_TPMINIPROJET_RATEOFFIREPOWERUP_H

#include "../PowerUp.h"
#include "../utils.h"

class RateOfFirePowerUp : public PowerUp {
public:
    RateOfFirePowerUp();

    PowerUp::Type getPowerUp() override;

};


#endif //CPP_QT_TPMINIPROJET_RATEOFFIREPOWERUP_H
