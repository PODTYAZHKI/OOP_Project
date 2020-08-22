#include "widget.h"
#include "ui_widget.h"
#include <iostream>

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->resize(600,600);
    this->setFixedSize(600,600);

    ui->setupUi(this);
    scene   = new CustomScene();    // сцена
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);  // сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // минус скролбары
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(0,0,520,520);   // размеры графической сцены


}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotBullet(QPointF start, QPointF end) // создание пули
{
    Bullet *bullet = new Bullet(start, end, hero);
    bullet->setCallbackFunc(slotHitEnemy);
    scene->addItem(bullet);
}

void Widget::slotCreateEnemy() // создание врага
{
    Enemy *enemy = new Enemy(hero);
    enemy->setZValue(2);
    scene->addItem(enemy);
    enemy->setPos(randomBetween(40, 480), randomBetween(40, 480));
    enemys.append(enemy);
    connect(enemy, &Enemy::signalCheckGameOver, this, &Widget::slotGameOver);
}

void Widget::slotGameOver() // слот на проигрыш
{
    timerEnemy->stop();
    foreach (QGraphicsItem *enemy, enemys) {
        scene->removeItem(enemy);   // Удаляем со сцены
        enemys.removeOne(enemy);    // Удаляем из списка
        delete enemy;
    }
    QMessageBox msgbox;
    msgbox.setText("Game Over!");
    if (msgbox.exec())
    {
        ui->btn_start->setEnabled(true);
        hero->deleteLater();
        scene->clear();

    }

}


void Widget::slotHitEnemy(QGraphicsItem *item)
{
    foreach (QGraphicsItem *targ, enemys) {
        if(targ == item){
            Enemy *t = qgraphicsitem_cast <Enemy *> (targ);
            t->hit(2); // урон
            if (t->isDead())
            {
            }
        }
    }
}



void Widget::on_btn_start_clicked()
{
    // cоздаем кастомизированный курсор из ресурсного файла
    QCursor cursor = QCursor(QPixmap(":/cursor/cursorTarget.png"));
    hero = new Hero();
    hero->setPos(60,60);
    hero->setZValue(2);
    scene->addItem(hero);
    ui->graphicsView->setMouseTracking(true); // отслеживание мыши
    connect(scene, &CustomScene::signalTargetCoordinate, hero, &Hero::slotTarget);
    connect(scene, &CustomScene::signalShot, hero, &Hero::slotShot);
    connect(hero, &Hero::signalBullet, this, &Widget::slotBullet);
    // стены
    scene->addRect(0,0,520,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(0,0,20,520,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(0,500,520,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(500,0,20,520,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    timerEnemy = new QTimer();
    connect(timerEnemy, &QTimer::timeout, this, &Widget::slotCreateEnemy);
    timerEnemy->start(3000);
    ui->btn_start->setEnabled(false);
}

QList<QGraphicsItem *> Widget::enemys; // реализация списка врагов
