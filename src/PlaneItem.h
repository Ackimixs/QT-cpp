#ifndef PLANE_H
#define PLANE_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "Utils.h"


class PlaneItem : public QGraphicsPixmapItem {


private :
    int speed;

public:

    PlaneItem(QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName)) {
        this->speed = Utils::randInt(1, 10);
    }

    void move();

    int getSpeed() const { return speed; }
    void setSpeed(int speed) { this->speed = speed; }


};

#endif // PLANE_H
