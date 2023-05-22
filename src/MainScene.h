#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QRectF>


#include "PlaneItem.h"

class MainScene : public QGraphicsScene {

    Q_OBJECT

private :
    QPixmap background;
    QTimer* timer;
    QVector<PlaneItem*> planeItems;

public:
    MainScene();
    void drawBackground(QPainter* painter, const QRectF& rect);
    const QVector<PlaneItem*>& getPlanes(){return planeItems;}

    virtual ~MainScene();

public slots :
    void update();


};

#endif // MYSCENE_H
