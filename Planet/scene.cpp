#include <QGraphicsSceneMouseEvent>
#include <chrono>

#include "scene.h"
#include "functions.h"


Scene::Scene(QObject *parent) :
    QGraphicsScene(parent)
    , physics(true)
    , t(&Scene::physicsThread, this)
{

}

Scene::~Scene()
{
    physics = false;
    t.join();
    clearAll();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    Circle *circle = qgraphicsitem_cast<Circle *>(item);

    if (event->button() == Qt::RightButton) {
        if(circle) {
            deleteCircle(circle);
        } else {
            addCircle(event->scenePos());
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void Scene::addCircle(QPointF pos)
{
    std::lock_guard<std::mutex> lock(circleMutex);
    Circle* new_cir = new Circle(pos);
    circleList << new_cir;
    addItem(new_cir);
}

void Scene::addCircle()
{
    std::lock_guard<std::mutex> lock(circleMutex);
    QPointF pos(random(0, this->width()), random(0, this->height()));
    Circle* new_cir = new Circle(pos);
    circleList << new_cir;
    addItem(new_cir);
}

void Scene::deleteCircle(Circle *circle)
{
    std::lock_guard<std::mutex> lock(circleMutex);
    circleList.removeOne(circle);
    removeItem(circle);
    delete circle;
}

void Scene::clearAll()
{
    std::lock_guard<std::mutex> lock(circleMutex);
    clear();
    circleList.clear();
}

QPointF Scene::getPowerToObject(Circle* circle1, Circle* circle2)
{
    QPointF pos1 = circle1->getPos();
    QPointF pos2 = circle2->getPos();

    qreal r = (distance(pos1, pos2) - 2 * RADIUS) / 50;
    qreal f = (1/r - 1/pow(r, 2)) / 10000;

    if (f < -3) f = -3;

    QPointF pos = pos2 - pos1;
    qreal alpha = atan2(pos.ry(), pos.rx());

    return QPointF(f * cos(alpha), f * sin(alpha));
}

void Scene::getPower()
{
    std::lock_guard<std::mutex> lock(circleMutex);

    static auto updateTime = std::chrono::system_clock::now();

    QList<Circle*> newCircleList;

    foreach (Circle* cir1, circleList) {

        QPointF pos1 = cir1->getPos();
        QPointF v1 = cir1->getV();

        QPointF result_vec(0, 0);

        foreach (Circle* cir2, circleList) {
            if(cir1 == cir2)
                continue;

            QPointF vec = getPowerToObject(cir1, cir2);
            result_vec += vec;
        }

        auto currentTime = std::chrono::system_clock::now();
        double t = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - updateTime).count();

        QPointF xy;
        xy.setX( pos1.rx() + v1.rx()*t + result_vec.rx()*t*t);
        xy.setY( pos1.ry() + v1.ry()*t + result_vec.ry()*t*t);
        QPointF V( v1.rx() + result_vec.rx()*t, v1.ry() + result_vec.ry()*t );

        Circle* cir_result = cir1;
        cir_result->setState(xy, V);
        newCircleList.append(cir_result);
    }

    for(int i = 0; i < circleList.size(); ++i) {
        circleList.at(i)->setState(newCircleList.at(i)->getPos(), newCircleList.at(i)->getV());
    }

    updateTime = std::chrono::system_clock::now();
}

void Scene::physicsThread()
{
    while(physics) {
        const auto start = std::chrono::system_clock::now();
        getPower();
        const auto end = std::chrono::system_clock::now();
        int difference = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        int sleep = MICRO / FPS - difference;
        if (sleep > 0)
            std::this_thread::sleep_for(std::chrono::microseconds(sleep));
    }
}

