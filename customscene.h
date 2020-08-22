#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomScene(QObject *parent = 0);
    ~CustomScene();

signals:
    void signalTargetCoordinate(QPointF point); // для курсора
    void signalShot(bool shot);

public slots:

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
