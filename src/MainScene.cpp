#include "MainScene.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QVector>
#include <iostream>

MainScene::MainScene() {

    this->background.load("panorama.jpg");
    this->setSceneRect(0, 0, background.width(), background.height());

    this->timer = new QTimer(this);
    this->timer->start(30);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->planeItems.push_back(new PlaneItem("plane_red.png"));
    this->planeItems.push_back(new PlaneItem("plane_green.png"));
    this->planeItems.push_back(new PlaneItem("plane_blue.png"));

    int nbPlaneItems = this->planeItems.size();

    for (unsigned int i = 0; i < nbPlaneItems; i++) {

        PlaneItem* planeItem = this->planeItems[i];

        this->addItem(planeItem);

        // all the planeItems on the right side of the scene
        planeItem->setPos(this->width()-50, this->height()/2 + 10*i);
    }

}

void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}


void MainScene::update() {

    int nbPlaneItems = planeItems.size();

    for (PlaneItem* planeItem : this->planeItems) {

        planeItem->move();

    }

    QList<QGraphicsView *> views = this->views();

    for (int i = views.length() - 1; i > 0; i--) {
        views[i]->centerOn(this->planeItems[i-1]);
    }

}

MainScene::~MainScene() {

    delete this->timer;

    for(PlaneItem* planeItem : this->planeItems){
        delete planeItem;
    }
}

