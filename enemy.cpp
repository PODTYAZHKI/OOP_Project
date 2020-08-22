#include "enemy.h"
#include "math.h"
#include "iostream"

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

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Enemy::Enemy(QGraphicsItem *target, QObject *parent)
{
    angle = randomBetween(0,360);
    normalizeAngle(angle);
    setHealth(10);
    setMaxHealth();
    this->target = target;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::slotGameTimer);
    timer->start(15);
}

Enemy::~Enemy()
{

}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(0,-15) << QPoint(12,15) << QPoint(-12,15);
    painter->setBrush(Qt::blue);
    painter->drawPolygon(polygon);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::blue);
    //painter->drawRect(-20,-20, (int)max_health,3);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Enemy::slotGameTimer()
{
    QLineF lineToTarget(QPointF(0, 0), mapFromItem(target, 0, 0));
    if (lineToTarget.length() >= 20){
        qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
        if (lineToTarget.dy() < 0)
            angleToTarget = TwoPi - angleToTarget;
        angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);
        if (angleToTarget > 0 && angleToTarget < Pi) {
            if(angleToTarget > Pi / 5){
                angle = -15;
            } else if(angleToTarget > Pi / 10){
                angle = -5;
            } else {
                angle = -1;
            }
        } else if (angleToTarget <= TwoPi && angleToTarget > (TwoPi - Pi)) {
            if(angleToTarget < (TwoPi - Pi / 5)){
                angle = 15;
            } else if(angleToTarget < (TwoPi - Pi / 10)){
                angle = 5;
            } else {
                angle = 1;
            }
        } else if(angleToTarget == 0) {
            angle = 0;
        }
        setRotation(rotation() + angle);
        setPos(mapToParent(0, -(qrand() % ((4 + 1) - 1) + 1)));
        QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(5, 7)
                                                           << mapToScene(-7, -7)
                                                           << mapToScene(7, -7));

        foreach (QGraphicsItem *item, foundItems) {
            if (item == this)
            {
                continue;
            }
            if(item == target){
                emit signalCheckGameOver();
            }
        }
    }

}

