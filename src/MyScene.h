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

#include "Player.h"
#include "Enemies.h"
#include "Database.h"

class MyScene : public QGraphicsScene {
    Q_OBJECT

public:
    MyScene(Database* db, QObject* parent = nullptr);
    virtual ~MyScene();

    void resizePlane(qreal sceneWidth, qreal sceneHeight);

    void setupGameOverScreen();

private:

    Database* db;

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

public slots:

    void handlePlayerCollision();

    void update();

    void gameOverFunc();

    void restartSlots();

signals:

    void gameOverSignal();
};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
