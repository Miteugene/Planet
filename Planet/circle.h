#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <mutex>

class Circle : public QGraphicsEllipseItem
{
public:
    Circle(): pos(QPointF(0,0)), v(QPointF(0,0))  {};
    Circle(QPointF pos, QPointF v = QPointF(0, 0), QGraphicsItem *parent = 0);


    void setState(QPointF pos, QPointF V = QPointF(0, 0));
    QPointF getPos();
    QPointF getV();
    qreal getRadius();

protected:
    void advance(int step);

private:
    QPointF pos;
    QPointF v;
    qreal radius;
    std::mutex stateMutex;
    QColor color;

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CIRCLE_H
