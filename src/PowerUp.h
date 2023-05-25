#ifndef CPP_QT_TPMINIPROJET_POWERUP_H
#define CPP_QT_TPMINIPROJET_POWERUP_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>

#include "utils.h"
#include "Logger.h"

class PowerUp : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum Type {
        Heal,
        RateOfFire,
        Null
    };

    PowerUp();

    ~PowerUp();

    virtual PowerUp::Type getPowerUp();

protected:
    PowerUp::Type type;

    QTimer* timer;


public slots:
    void update();
};


#endif //CPP_QT_TPMINIPROJET_POWERUP_H
