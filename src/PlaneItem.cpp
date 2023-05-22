#include "PlaneItem.h"
#include "Utils.h"

#include <QPointF>

void PlaneItem::move() {

    QPointF pos = this->pos();

    int newX = pos.x() - speed;

    if (newX < 0) {
        speed = Utils::randInt(1, 10) - 10;
    }

    if (newX > this->scene()->width()) {
        speed = Utils::randInt(1, 10);
    }

    this->setPos(newX, pos.y());
}


