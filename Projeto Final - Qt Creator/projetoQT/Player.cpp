#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QSoundEffect>

Player::Player(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent)
{
    bulletsound = new QSoundEffect(this);
    bulletsound->setSource(QUrl("qrc:/sounds/bullet.wav"));
    bulletsound->setVolume(0.5f);

    QPixmap pix(":/images/player.png");
    setPixmap(pix.scaled(80, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Player::keyPressEvent(QKeyEvent *event){
    // move the player left and right
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
            setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
            setPos(x()+10,y());
    }
    // shoot with the spacebar
    else if (event->key() == Qt::Key_Space){
        //play the sound
        bulletsound->play();

        // create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(x(),y());
        scene()->addItem(bullet);
    }
}

void Player::spawn(){
    // create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}