#include <QCoreApplication>
#include "MyScene.h"

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent), gameOver(false) {

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->player = new Player(":/assets/img/player/11.png");
    this->player->setFlag(QGraphicsItem::ItemIsFocusable);
    this->player->setFocus();
    this->addItem(this->player);
    this->addItem(this->player->lifePointText);
    this->player->lifePointText->setPos(30, 30);
    this->addItem(this->player->scoreText);
    this->player->scoreText->setPos(90, 30);

    connect(this->player, SIGNAL(gameOverFunc()), this, SLOT(gameOverFunc()));
    connect(this->player, SIGNAL(gameRestartSignal()), this, SLOT(restartSlots()));

    QMediaPlayer* audioPlayer = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioPlayer->setAudioOutput(audioOutput);
    audioPlayer->setSource(QUrl("qrc:/assets/sounds/gameLevelSound.wav"));
    audioOutput->setVolume(0.1f);
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

}

MyScene::~MyScene() {
    this->timer->destroyed();
    Database::closeDB();
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
        this->timer->start(4000 - int(3700 * (1 - exp(-0.01 * this->player->getScore()))));
    } else if (this->difficultyLevel == GameLevel::MEDIUM) {
        this->timer->start(3000 - int(2800 * (1 - exp(-0.01 * this->player->getScore()))));
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
    connect(this->gameOverRestartButton, SIGNAL(pressed()), this, SLOT(restartSlots()));
    connect(this->gameOverQuitButton, SIGNAL(pressed()), this, SLOT(quitSlot()));


    this->gameOverLayout->addWidget(this->userScoreText);
    this->gameOverLayout->addWidget(this->leaderBoardText);
    this->gameOverLayout->addWidget(this->gameOverLeaderBoard);
    this->gameOverLayout->addWidget(this->gameOverRestartButton);
    this->gameOverLayout->addWidget(this->gameOverQuitButton);

    this->gameOverWidget->hide();
}

void MyScene::startSlot() {


    this->playerName = this->playerNameInput->text();
    this->difficultyLevel = this->difficulty->currentIndex();

    if (this->playerName.length() == 0) {
        return;
    } else {
        Logger::log({"Game"}, Logger::Debug, "Player name : " + this->playerName + " difficulty : " + QString::number(this->difficultyLevel) , true);

        switch (this->difficultyLevel) {
            case GameLevel::EASY:
                this->player->setDifficulty(0);
                this->timer->start(4000);
                break;
            case GameLevel::MEDIUM:
                this->player->setDifficulty(1);
                this->timer->start(3000);
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
        this->quit->hide();
        this->player->startGame();
        this->player->setFocus();
        emit startGameSignal();
    }
}

void MyScene::quitSlot() {
    emit quitGameSignal();
}

void MyScene::addEnemie() {
    QString path = ":/assets/img/enemies/" + QString::number(Utils::randInt(1, 10)) + ".png";
    Enemies* newEnemies = new Enemies(path);
    this->addItem(newEnemies);

    int x = Utils::randInt(newEnemies->pixmap().width() + 10, this->width() - (newEnemies->pixmap().width() + 10));
    int y = Utils::randInt(20, 300);

    connect(newEnemies, SIGNAL(reachEndOfMapSignal()), this, SLOT(handlePlayerCollision()));
    connect(newEnemies, SIGNAL(collisionWithPlayerSignal()), this, SLOT(handlePlayerCollision()));
    connect(this, SIGNAL(gameOverSignal()), newEnemies, SLOT(gameOverSlot()));

    newEnemies->setPos(x, y);
}