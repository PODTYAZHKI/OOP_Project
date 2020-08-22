#include <math.h>
#include "character.h"


Character::Character(QObject *parent):
    QObject(parent), QGraphicsItem()
{
    maxHealth = 100;
}

Character::~Character()
{

}

QRectF Character::boundingRect() const
{
    return QRectF(-12,-15,24,30);
}

QPainterPath Character::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Character::setHealth(int i)
{
    health=i;
}

void Character::setMaxHealth()
{
    maxHealth=health;
}



void Character::hit(int damage)
{
    this->health -= damage;
    //        this->update(QRectF(-20,-20,40,40));
    if(health <= 0)
    {
        this->deleteLater();
        dead = true;
    }
}

bool Character::isDead()
{
    return dead;
}

