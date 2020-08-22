#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPolygon>
#include <QTimer>
#include <QDebug>
#include <QCursor>

#include <Windows.h>

class Character : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Character(QObject *parent = 0);
    ~Character();
    void hit(int damage);
    void setHealth(int i);
    void setMaxHealth();
    bool isDead();

public slots:

private:
    QRectF boundingRect() const;
    QPainterPath shape() const;  // для обработки столкновений

private:
    int health;
    int maxHealth;
    bool dead = false;

};

#endif // CHARACTER_H
