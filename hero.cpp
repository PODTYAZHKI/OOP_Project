#include "hero.h"
#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Hero::Hero(QObject *parent)
{
    setRotation(0);
    target = QPointF(0,0);
    shot = false;
    setHealth(10);
    setMaxHealth();
    gameTimer = new QTimer();   // главный таймер
    connect(gameTimer, &QTimer::timeout, this, &Hero::slotGameTimer);
    gameTimer->start(5);
    bulletTimer = new QTimer(); // таймер создания пуль
    connect(bulletTimer, &QTimer::timeout, this, &Hero::slotBulletTimer);
    bulletTimer->start(1000/6);
}

Hero::~Hero()
{
}

void Hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(0,-15) << QPoint(12,15) << QPoint(-12,15);
    painter->setBrush(Qt::red);
    painter->drawPolygon(polygon);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    //painter->drawRect(-20,-20, (int)max_health,3);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Hero::slotTarget(QPointF point)
{
    target = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);
    if (angleToTarget >= 0 && angleToTarget < Pi) {
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}

void Hero::slotShot(bool shot)
{
    this->shot = shot;
}

void Hero::slotGameTimer()
{
    // перемещение героя
    if(GetAsyncKeyState('A')){
        this->setX(this->x() - 1);
        if(!scene()->collidingItems(this).isEmpty()){
            this->setX(this->x() + 1);
        }
    }
    if(GetAsyncKeyState('D')){
        this->setX(this->x() + 1);
        if(!scene()->collidingItems(this).isEmpty()){
            this->setX(this->x() - 1);
        }
    }
    if(GetAsyncKeyState('W')){
        this->setY(this->y() - 1);
        if(!scene()->collidingItems(this).isEmpty()){
            this->setY(this->y() + 1);
        }
    }
    if(GetAsyncKeyState('S')){
        this->setY(this->y() + 1);
        if(!scene()->collidingItems(this).isEmpty()){
            this->setY(this->y() - 1);
        }
    }

    // проверка на выход за поле
    if(this->x() - 30 < 0){
        this->setX(30);         // слева
    }
    if(this->x() + 30 > 520){
        this->setX(520 - 30);   // справа
    }

    if(this->y() - 30 < 0){
        this->setY(30);         // сверху
    }
    if(this->y() + 30 > 520){
        this->setY(520 - 30);   // снизу
    }

    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);
    if (angleToTarget >= 0 && angleToTarget < Pi) {
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}

void Hero::slotBulletTimer()
{
    // сигнал на создание пули
    if(shot) emit signalBullet(mapToScene(0,-25), target);

}

