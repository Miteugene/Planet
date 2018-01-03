#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

#include "circle.h"
#include "scene.h"

#include <QPushButton>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void pushButtonClick();
    void clearButtonClick();

private:
    Ui::Widget *ui;
    Scene *scene;
    QTimer* frameTimer;
};

#endif // WIDGET_H
