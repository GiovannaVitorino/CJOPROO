#include "Game.h"
#include "Enemy.h"

#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QAudioOutput>

Game::Game(QWidget *parent)
    : QGraphicsView(parent)
{
    // Cria a cena
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,800,600);
    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));

    setScene(scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize(800,600);

    // Cria o jogador
    player = new Player();

    player->setPos(400,500);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);

    // Score
    score = new Score();
    scene->addItem(score);

    // Health
    health = new Health();
    health->setPos(health->x(), health->y()+25);
    scene->addItem(health);

    // spawn enemies
    /*QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000);*/

    QTimer *timer = new QTimer(this);

    connect(timer,
            &QTimer::timeout,
            player,
            &Player::spawn);

    timer->start(2000);

    // Música
    QMediaPlayer *music = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);

    music->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.5);

    music->setSource(QUrl("qrc:/sounds/bgsound.mp3"));
    music->play();

    show();
}