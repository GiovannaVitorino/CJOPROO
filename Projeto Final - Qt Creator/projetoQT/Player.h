#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
//#include <QMediaPlayer>
#include <QSoundEffect>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
private:
    QSoundEffect  * bulletsound;
    //QMediaPlayer * bulletsound;
};

#endif // PLAYER_H