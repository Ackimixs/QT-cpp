#include "MyScene.h"

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent), gameOver(false) {
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(3000);

    this->player = new Player(":/assets/img/player/Aircraft_07.png");
    this->player->setFlag(QGraphicsItem::ItemIsFocusable);
    this->player->setFocus();
    this->addItem(this->player);
    this->addItem(this->player->lifePointText);
    this->player->lifePointText->setPos(30, 30);
    this->addItem(this->player->scoreText);
    this->player->scoreText->setPos(90, 30);

    connect(this->player, SIGNAL(gameOverFunc()), this, SLOT(gameOverFunc()));
    connect(this->player, SIGNAL(gameRestartSignal()), this, SLOT(restartSlots()));
}

MyScene::~MyScene() {
    this->timer->destroyed();
}

void MyScene::update() {

    if (this->gameOver) {
        this->timer->stop();
        return;
    }

    Enemies* newEnemies = new Enemies(":/assets/img/player/Aircraft_01.png");
    this->addItem(newEnemies);

    int x = Utils::randInt(newEnemies->pixmap().width() + 10, this->width() - (newEnemies->pixmap().width() + 10));
    int y = Utils::randInt(20, 300);

    connect(newEnemies, SIGNAL(collisionWithPlayerSignal()), this, SLOT(handlePlayerCollision()));
    connect(this, SIGNAL(gameOverSignal()), newEnemies, SLOT(gameOverSlot()));
    newEnemies->setPos(x, y);
}

void MyScene::resizePlane(qreal sceneWidth, qreal sceneHeight) {
    this->player->setPos((sceneWidth / 2) - (this->player->pixmap().width() / 2), sceneHeight - this->player->pixmap().height() - 20);
}

void MyScene::handlePlayerCollision() {
    this->player->removeOneLife();
}

void MyScene::gameOverFunc() {
    this->gameOver = true;
    emit gameOverSignal();
}

void MyScene::restartSlots() {
    QList<QGraphicsItem *> items = this->items();

    for (int i = 0; i < items.count(); i++) {
        if (typeid(*items[i]) != typeid(Player) && typeid(*items[i]) != typeid(QGraphicsTextItem)) {
            delete (items[i]);
        }
    }

    this->player->reset();
    this->resizePlane(400, 800);

    Logger::log({"Game"}, Logger::Debug, "Game fully restarted", true);
}