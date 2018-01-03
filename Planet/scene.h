#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <vector>
#include <thread>
#include <atomic>

#include "circle.h"

class Scene : public QGraphicsScene
{
public:
    Scene(QObject *parent = Q_NULLPTR);
    ~Scene();

    void addCircle(QPointF pos);
    void addCircle();
    void deleteCircle(Circle *circle);
    void clearAll();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

public:
    QList<Circle*> circleList;
    std::mutex circleMutex;
    std::atomic<bool> physics;
    std::thread t;

    void physicsThread();
    void getPower();
    QPointF getPowerToObject(Circle* circle1, Circle* circle2);

};

#endif // SCENE_H
