#ifndef HERO_H
#define HERO_H

#include "character.h"

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPolygon>
#include <QTimer>
#include <QDebug>
#include <QCursor>

#include <Windows.h>

class Hero : public Character
{
    Q_OBJECT
public:
    Hero(QObject *parent = 0);
    ~Hero();

signals:
    void signalBullet(QPointF start, QPointF end); // создание пули

public slots:
    void slotTarget(QPointF point); // курсор
    void slotShot(bool shot); // разрешение стрельбы

private slots:
    void slotGameTimer();   /// главный таймер героя
    void slotBulletTimer(); /// таймер проверки пули

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPointF target;         // курсор
    bool shot;              // состояния стрельбы
    QTimer *bulletTimer;    // таймер пули
    QTimer *gameTimer;      // главный таймер героя
};

#endif // HERO_H
