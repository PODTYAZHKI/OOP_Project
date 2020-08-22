#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>
#include <QDebug>

#include <sprite.h>

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Bullet(QPointF start, QPointF end, QGraphicsItem *hero, QObject *parent = 0);
    ~Bullet();
    /// Установка CallBack функции
    void setCallbackFunc(void (*func) (QGraphicsItem * item));

signals:


public slots:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /// Объявляем сигнатуру CallBack функции
    void (*callbackFunc)(QGraphicsItem * item);

private:
    QTimer *timerBullet;
    QGraphicsItem *hero;
private slots:
    void slotTimerBullet();
};

#endif // BULLET_H
