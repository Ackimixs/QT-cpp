#include <QCoreApplication>
#include "MyScene.h"

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent), gameOver(false) {

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->player = new Player(":/assets/img/player/" + SettingsManager::getInstance().value("selectedShip").toString() + ".png");
    this->player->setFlag(QGraphicsItem::ItemIsFocusable);
    this->player->setFocus();
    this->addItem(this->player);
    this->addItem(this->player->lifePointText);
    this->player->lifePointText->setPos(30, 30);
    this->addItem(this->player->scoreText);
    this->player->scoreText->setPos(90, 30);

    connect(this->player, SIGNAL(gameOverFunc()), this, SLOT(gameOverFunc()));
    connect(this->player, SIGNAL(gameRestartSignal()), this, SLOT(restartSlots()));

    this->mainVolume = SettingsManager::getInstance().value("mainMusicLevel").toInt();
    this->gameVolume = SettingsManager::getInstance().value("gameMusicLevel").toInt();

    QMediaPlayer* audioPlayer = new QMediaPlayer;
    this->audioOutput = new QAudioOutput;
    audioPlayer->setAudioOutput(this->audioOutput);
    audioPlayer->setSource(QUrl("qrc:/assets/sounds/gameLevelSound.wav"));
    this->audioOutput->setVolume((this->mainVolume / 100) * (this->gameVolume / 100));
    audioPlayer->setLoops(QMediaPlayer::Infinite);
    audioPlayer->play();


    this->difficulty = new QComboBox();
    this->difficulty->addItem("easy");
    this->difficulty->addItem("medium");
    this->difficulty->addItem("hard");
    this->difficulty->addItem("impossible");
    this->difficulty->addItem("Are u ok ?");
    this->difficulty->addItem("power up mode");

    this->playerNameInput = new QLineEdit();
    this->start = new QPushButton("start");
    this->quit = new QPushButton("quit");

    this->playerNameInput->setPlaceholderText("username");
    // Set the background color to transparent
    QString styleSheet = "background-color: transparent; color: black;";
    this->playerNameInput->setStyleSheet(styleSheet);

    this->addWidget(this->playerNameInput);
    this->addWidget(this->start);
    this->addWidget(this->quit);
    this->addWidget(this->difficulty);

    int bxPos = 110;
    this->playerNameInput->setGeometry(bxPos, 250, 200, 50);
    this->difficulty->setGeometry(bxPos, 310, 200, 50);
    this->start->setGeometry(bxPos, 370, 200, 50);
    this->quit->setGeometry(bxPos, 430, 200, 50);

    connect(this->start, SIGNAL(pressed()), this, SLOT(startSlot()));
    connect(this->quit, SIGNAL(pressed()), this, SLOT(quitSlot()));

    Database::setupDB();

    // shop screen
    setupShopScreen();

}

MyScene::~MyScene() {
    this->timer->destroyed();
    this->player->destroyed();
    Database::closeDB();

    delete this->player;
    delete this->timer;
}

void MyScene::update() {

    if (this->gameOver) {
        this->timer->stop();
        return;
    }

    int nbEnemies = 1;
    if (this->difficultyLevel == GameLevel::HARD || this->difficultyLevel == GameLevel::POWERUP || this->difficultyLevel == GameLevel::IMPOSSIBLE) {
        nbEnemies = 2;
    } else if (this->difficultyLevel == GameLevel::AREUOK) {
        nbEnemies = 3;
    }

    for (int i = 0; i < nbEnemies; i++) {
        this->addEnemie();
    }

    this->timer->stop();
    if (this->difficultyLevel == GameLevel::EASY) {
        this->timer->start(3000 - int(2800 * (1 - exp(-0.01 * this->player->getScore()))));
    } else if (this->difficultyLevel == GameLevel::MEDIUM) {
        this->timer->start(2500 - int(2300 * (1 - exp(-0.01 * this->player->getScore()))));
    } else if (this->difficultyLevel == GameLevel::HARD) {
        this->timer->start(2000 - int(1800 * (1 - exp(-0.01 * this->player->getScore()))));
    } else if (this->difficultyLevel == GameLevel::IMPOSSIBLE) {
        this->timer->start(1000 - int(900 * (1 - exp(-0.01 * this->player->getScore()))));
    } else if (this->difficultyLevel == GameLevel::AREUOK) {
        this->timer->start(500 - int(400 * (1 - exp(-0.01 * this->player->getScore()))));
    } else if (this->difficultyLevel == GameLevel::POWERUP) {
        this->timer->start(1500 - int(1300 * (1 - exp(-0.01 * this->player->getScore()))));
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

    SettingsManager::getInstance().setValue("money", SettingsManager::getInstance().value("money").toInt() + score);
    Database::insert("INSERT INTO leaderboard (player, score, difficulty) VALUES ('"+ this->playerName +"', " + QString::number(score) +", "+ QString::number(this->difficultyLevel) +")");

    this->userScoreText->setText("your score : " + QString::number(score));
    this->leaderBoardText->setText("Leaderboard");

    this->gameOverLeaderBoard->clear();

    QList<QMap<QString, QString>> data = Database::query("SELECT * FROM leaderboard WHERE difficulty = "+ QString::number(this->difficultyLevel) +" ORDER BY score DESC;");
    for (int i = 0; i < data.count(); i++) {
        this->gameOverLeaderBoard->append(data[i].value("player") + " : " + data[i].value("score") + " - " + data[i].value("date").mid(0, 10));
    }

    this->gameOverWidget->raise();
}

void MyScene::restartSlots(int difficultyLevel) {

    if (difficultyLevel != -1) {
        this->difficultyLevel = difficultyLevel;
        this->player->setDifficulty(difficultyLevel);
    }

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

    if (this->difficultyLevel == 0) {
        this->timer->start(3000);
    } else {
        this->timer->start(1500);
    }

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
    this->gameOverQuitButton = new QPushButton("Quit !");
    this->gameOverHomeButton = new QPushButton("Home");
    connect(this->gameOverRestartButton, SIGNAL(pressed()), this, SLOT(restartSlots()));
    connect(this->gameOverQuitButton, SIGNAL(pressed()), this, SLOT(quitSlot()));
    connect(this->gameOverHomeButton, SIGNAL(pressed()), this, SLOT(homeSlot()));


    this->gameOverLayout->addWidget(this->userScoreText);
    this->gameOverLayout->addWidget(this->leaderBoardText);
    this->gameOverLayout->addWidget(this->gameOverLeaderBoard);
    this->gameOverLayout->addWidget(this->gameOverRestartButton);
    this->gameOverLayout->addWidget(this->gameOverQuitButton);
    this->gameOverLayout->addWidget(this->gameOverHomeButton);

    this->gameOverWidget->hide();
}

void MyScene::startSlot() {
    this->gameOver = false;
    this->playerName = this->playerNameInput->text();
    this->difficultyLevel = this->difficulty->currentIndex();
    this->player->reset();

    if (this->playerName.length() == 0) {
        return;
    } else {
        Logger::log({"Game"}, Logger::Debug, "Player name : " + this->playerName + " difficulty : " + QString::number(this->difficultyLevel) , true);

        switch (this->difficultyLevel) {
            case GameLevel::EASY:
                this->player->setDifficulty(0);
                this->timer->start(3000);
                break;
            case GameLevel::MEDIUM:
                this->player->setDifficulty(1);
                this->timer->start(2500);
                break;
            case GameLevel::HARD:
                this->player->setDifficulty(2);
                this->timer->start(2000);
                break;
            case GameLevel::IMPOSSIBLE:
                this->player->setDifficulty(3);
                this->timer->start(1000);
                break;
            case GameLevel::AREUOK:
                this->player->setDifficulty(4);
                this->timer->start(500);
                break;
            case GameLevel::POWERUP:
                this->player->setDifficulty(5);
                this->timer->start(1500);
                break;
        }

        this->playerNameInput->hide();
        this->difficulty->hide();
        this->start->hide();
        this->moneyText->hide();
        this->quit->hide();
        this->shopWidget->hide();
        this->iconShop->hide();
        this->player->startGame();
        this->player->setFocus();
        emit startGameSignal();
    }
}

void MyScene::quitSlot() {
    emit quitGameSignal();
}

void MyScene::addEnemie() {
    QString path = ":/assets/img/enemies/" + QString::number(Utils::randInt(2, 5)) + ".png";
    Enemies* newEnemies = new Enemies(path);
    this->addItem(newEnemies);

    int x = Utils::randInt(newEnemies->pixmap().width() + 10, this->width() - (newEnemies->pixmap().width() + 10));
    int y = Utils::randInt(20, 300);

    connect(newEnemies, SIGNAL(reachEndOfMapSignal()), this, SLOT(handlePlayerCollision()));
    connect(newEnemies, SIGNAL(collisionWithPlayerSignal()), this, SLOT(handlePlayerCollision()));
    connect(this, SIGNAL(gameOverSignal()), newEnemies, SLOT(gameOverSlot()));

    newEnemies->setPos(x, y);
}

void MyScene::setupShopScreen() {
    this->shopWidget = new QWidget();
    this->shopLayout = new QGridLayout();

    for (int i = 1; i < 10; i++) {
        SkinCardWidget* card = new SkinCardWidget(QString::number(i), QColor(Qt::blue), 10 * (i * 4));

        this->shopLayout->addWidget(card, (i-1) / 2, (i-1) % 2);

        connect(card, SIGNAL(changeShipSelect()), this, SLOT(changeSkin()));
        connect(card, SIGNAL(shipBought()), this, SLOT(updateMoney()));
    }

    this->iconShop = new QPushButton();
    QIcon icon(":/assets/img/icon/shop.png");
    this->iconShop->setIcon(icon);
    this->iconShop->setIconSize(QSize(32, 32));
    this->iconShop->setGeometry(400 - 32, 0, 32, 32);

    addWidget(this->iconShop);

    connect(this->iconShop, SIGNAL(pressed()), this, SLOT(handleShowShop()));

    this->addWidget(this->shopWidget);
    this->shopWidget->setLayout(this->shopLayout);
    this->shopWidget->setGeometry(25, 100, 400 - 50, 800 - 200);

    this->shopWidget->hide();

    this->isShopOpen = false;
    this->moneyText = new QLabel("Money : " + SettingsManager::getInstance().value("money").toString());
    this->moneyText->setWindowOpacity(1);

    this->addWidget(this->moneyText);
    this->moneyText->setGeometry(400 - (200 + this->iconShop->width()), 0, 200, this->iconShop->height());
}

void MyScene::updateMoney() {
    this->moneyText->setText("Money : " + SettingsManager::getInstance().value("money").toString());
}

void MyScene::handleShowShop() {
    if (this->isShopOpen) {
        this->shopWidget->hide();

        this->start->show();
        this->quit->show();
        this->playerNameInput->show();
        this->difficulty->show();

        this->isShopOpen = !this->isShopOpen;
    } else {
        this->shopWidget->show();

        this->start->hide();
        this->quit->hide();
        this->playerNameInput->hide();
        this->difficulty->hide();

        this->isShopOpen = !this->isShopOpen;
    }
}

void MyScene::changeSkin() {
    QString d = SettingsManager::getInstance().value("selectedShip").toString();
    this->player->changePixmap(d);
}

void MyScene::homeSlot() {
    this->gameOverWidget->hide();
    this->playerNameInput->show();
    this->difficulty->show();
    this->start->show();
    this->quit->show();
    this->iconShop->show();
    this->shopWidget->hide();
    this->moneyText->show();
    this->moneyText->setText("Money : " + SettingsManager::getInstance().value("money").toString());
    this->player->setPos(this->width() / 2, this->height() - 100);
    this->player->show();
}

void MyScene::updateSettings() {
    this->mainVolume = SettingsManager::getInstance().value("mainMusicLevel").toInt();
    this->gameVolume = SettingsManager::getInstance().value("gameMusicLevel").toInt();
    qInfo() << SettingsManager::getInstance().value("mainMusicLevel").toInt();
    this->player->volumeChanged();
    this->audioOutput->setVolume((this->mainVolume / 100) * (this->gameVolume / 100));
}