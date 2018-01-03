#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QPointF>
#include <math.h>

#define FPS 60 //частота кадров
#define RADIUS 20 //радиус шариков
#define SCALE 1000 //масштаб

#define MICRO 1000000

#define minCircles 5 //минимальное количество шариков в созданном мире
#define maxCircles 10 //максимальное количество шариков в созданном мире

inline int random(int low, int high) {
    return (qrand() % ((high + 1) - low) + low);
}

inline qreal distance(QPointF p1, QPointF p2) {
    return sqrt(pow(p2.rx() - p1.rx(), 2) + pow(p2.ry() - p1.ry(), 2));
}

#endif // FUNCTIONS_H
