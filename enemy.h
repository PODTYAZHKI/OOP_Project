#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include "character.h"

class Enemy : public Character
{
    Q_OBJECT
public:
    Enemy(QGraphicsItem *target,  QObject *parent = 0);
    ~Enemy();


signals:
    void signalCheckGameOver();


private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    qreal angle;
    QGraphicsItem * target;
    QTimer  *timer;

private slots:
    void slotGameTimer();
};


#endif // ENEMY_H
