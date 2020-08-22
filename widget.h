#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>

#include <customscene.h>
#include <bullet.h>
#include <enemy.h>
#include <hero.h>

#include <QMessageBox>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    CustomScene  *scene; // графическая сцена
    Hero *hero; // создание героя
    QTimer *timerEnemy;  // Таймер для создания врагов
    static QList<QGraphicsItem *> enemys;  // Список врагов

    static void slotHitEnemy(QGraphicsItem *item);
    bool isDead;

private slots:
    void slotBullet(QPointF start, QPointF end); // cлот создания пули
    void slotCreateEnemy();
    void on_btn_start_clicked();
    void slotGameOver();
};

#endif // WIDGET_H
