#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGraphicsWidget>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QTextItem>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLineEdit>
#include <QComboBox>

#include "Player.h"
#include "Enemies.h"
#include "Database.h"

class MyScene : public QGraphicsScene {
    Q_OBJECT

public:
    MyScene(QObject* parent = nullptr);
    virtual ~MyScene();

    void resizePlane(qreal sceneWidth, qreal sceneHeight);

    void setupGameOverScreen();

private:

    QLineEdit* playerNameInput;
    QString playerName;
    int difficultyLevel;
    QPushButton* start;
    QPushButton* quit;
    QComboBox* difficulty;

    QTimer* timer;
    Player* player;
    bool gameOver;

    //Game Over
    QLabel* userScoreText = nullptr;
    QLabel* leaderBoardText = nullptr;
    QTextEdit* gameOverLeaderBoard = nullptr;
    QWidget* gameOverWidget = nullptr;
    QVBoxLayout* gameOverLayout = nullptr;
    QPushButton* gameOverRestartButton = nullptr;
    QPushButton* gameOverQuitButton = nullptr;

public slots:

    void handlePlayerCollision();

    void update();

    void gameOverFunc();

    void restartSlots(int difficultyLevel = -1);

    void startSlot();

    void quitSlot();

    void addEnemie();
signals:

    void gameOverSignal();

    void startGameSignal();

    void quitGameSignal();
};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
