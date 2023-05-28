#include "MyScene.h"

MyScene::MyScene(Database* db, QObject* parent) : QGraphicsScene(parent), gameOver(false), db(db) {
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

    this->timer->stop();
    if (this->player->getScore() > 0) {
        this->timer->start(3000 - int(2600 * (1 - exp(-0.01 * this->player->getScore()))));
    } else {
        this->timer->start(3000);
    }
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

    QList<QGraphicsItem *> items = this->items();

    for (int i = 0; i < items.count(); i++) {
        if (typeid(*items[i]) == typeid(Enemies) || typeid(*items[i]) == typeid(Bullet)) {
            delete (items[i]);
        }
    }

    this->gameOverWidget->show();

    qreal score = this->player->getScore();
    this->db->insert("INSERT INTO leaderboard (player, score) VALUES ('ackimixs', " + QString::number(score) +")");

    this->userScoreText->setText("your score : " + QString::number(score));
    this->leaderBoardText->setText("Leaderboard");

    this->gameOverLeaderBoard->clear();

    QList<QMap<QString, QString>> data = this->db->query("SELECT * FROM leaderboard ORDER BY score DESC;");
    for (int i = 0; i < data.count(); i++) {
        this->gameOverLeaderBoard->append(data[i].value("player") + " : " + data[i].value("score") + " - " + data[i].value("date").mid(0, 10));
    }

    this->gameOverWidget->raise();
}

void MyScene::restartSlots() {

    this->gameOverWidget->hide();

    QList<QGraphicsItem *> items = this->items();

    for (int i = 0; i < items.count(); i++) {
        if (typeid(*items[i]) == typeid(Enemies) || typeid(*items[i]) == typeid(Bullet)) {
            delete (items[i]);
        }
    }

    this->player->reset();
    this->resizePlane(400, 800);

    this->gameOver = false;

    this->timer->start(3000);

    this->player->setFocus();

    Logger::log({"Game"}, Logger::Debug, "Game fully restarted", true);
}

void MyScene::setupGameOverScreen() {
    //GAME OVER
    this->gameOverWidget = new QWidget();
    this->addWidget(this->gameOverWidget);
    this->gameOverWidget->setGeometry(25, 100, this->width() - 50, this->height() - 200);
    this->gameOverWidget->setWindowOpacity(0.7);
    this->gameOverLayout = new QVBoxLayout();
    this->gameOverWidget->setLayout(this->gameOverLayout);
    this->gameOverLeaderBoard = new QTextEdit();
    QFont font = this->gameOverLeaderBoard->font();
    font.setPointSize(16);
    this->gameOverLeaderBoard->setFont(font);
    this->gameOverLeaderBoard->setReadOnly(true);

    this->userScoreText = new QLabel();
    this->leaderBoardText = new QLabel();
    this->gameOverRestartButton = new QPushButton("Restart !");
    connect(this->gameOverRestartButton, SIGNAL(pressed()), this, SLOT(restartSlots()));

    this->gameOverLayout->addWidget(this->userScoreText);
    this->gameOverLayout->addWidget(this->leaderBoardText);
    this->gameOverLayout->addWidget(this->gameOverLeaderBoard);
    this->gameOverLayout->addWidget(this->gameOverRestartButton);

    this->gameOverWidget->hide();
}