#ifndef CPP_QT_TPMINIPROJET_EXPLOSION_H
#define CPP_QT_TPMINIPROJET_EXPLOSION_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

#include "Logger.h"

class Explosion : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Explosion(QGraphicsItem* parent = nullptr);

    ~Explosion();

    qreal state;

    QTimer* timer;

public slots:
    void update();

};


#endif //CPP_QT_TPMINIPROJET_EXPLOSION_H
