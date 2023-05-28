#include "Enemies.h"

Enemies::Enemies(QString filename, QGraphicsPixmapItem *parent) : QObject(), QGraphicsPixmapItem(parent), gameOver(false) {
    //Logger::log({"Enemies"}, Logger::Create, "Creating enemies", true);
    QPixmap img(filename);
    this->setPixmap(img.scaled(70, 70, Qt::KeepAspectRatio));
    this->setRotation(180);

    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(move()));
    this->timer->start(100);
}

Enemies::~Enemies() {
    //Logger::log({"Enemies"}, Logger::Delete, "Enemies deleted", true);
    this->timer->stop();
    delete this->timer;
}

void Enemies::move() {

    if (gameOver) {
        this->timer->stop();
        return;
    }

    int newX = Utils::randInt(-4, 5);
    int newY = Utils::randInt(-4, 5);

    int rand = Utils::randInt(0, 17);
    if (rand == 2) {
        Bullet* bullet = new Bullet(":/assets/img/bullet/fire_ball_1.png", Bullet::enemieBullet, 90, 10);
        this->scene()->addItem(bullet);
        bullet->setPos(this->x() - this->pixmap().width() / 2, this->y());

        connect(bullet, SIGNAL(collisionWithPlayerSignal()), this, SLOT(collisionWithPlayerSlot()));
        connect(this, SIGNAL(gameOverSignal()), bullet, SLOT(gameOverSlot()));
    }

    this->setPos(this->x() + newX, this->y() + newY);
}

void Enemies::collisionWithPlayerSlot() {
    emit collisionWithPlayerSignal();
}

void Enemies::gameOverSlot() {
    this->gameOver = true;
    emit this->gameOverSignal();
}