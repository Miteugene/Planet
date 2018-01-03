#include <QCursor>
#include <QPainter>

#include "circle.h"
#include "functions.h"


Circle::Circle(QPointF pos, QPointF v, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent)
{
    this->pos = pos;
    this->v = v;
    this->radius = RADIUS;
    color = QColor(random(50, 255), random(50, 255), random(50, 255));
    //this->setPos(pos);
}

void Circle::setState(QPointF pos, QPointF v)
{
    std::lock_guard<std::mutex> lock(stateMutex);
    this->pos = pos;
    this->v = v;
}

QPointF Circle::getPos()
{
    std::lock_guard<std::mutex> lock(stateMutex);
    return pos;
}

QPointF Circle::getV()
{
    std::lock_guard<std::mutex> lock(stateMutex);
    return v;
}

qreal Circle::getRadius()
{
    std::lock_guard<std::mutex> lock(stateMutex);
    return radius;
}

QPainterPath Circle::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

QRectF Circle::boundingRect() const
{
    return QRectF(-radius, -radius, 2*radius, 2*radius);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(color);
    painter->drawEllipse(-radius, -radius, 2*radius, 2*radius);
}

void Circle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setState(mapToScene(event->pos()));
}

void Circle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    setState(mapToScene(event->pos()));
}

void Circle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
}

void Circle::advance(int step)
{
    if (!step)
        return;
    this->setPos(getPos());
}
