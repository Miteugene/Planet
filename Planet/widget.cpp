#include <QDateTime>

#include "widget.h"
#include "ui_widget.h"
#include "functions.h"

#include <QGraphicsView>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->showMaximized();

    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);

    QGraphicsView* graphicsView = new QGraphicsView();


    QPushButton* pushButton = new QPushButton("Создать мир", this);
    connect(pushButton, SIGNAL(clicked()), SLOT(pushButtonClick()));

    QPushButton* clearButton = new QPushButton("Удалить все", this);
    connect(clearButton, SIGNAL(clicked()), SLOT(clearButtonClick()));


    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(clearButton);
    mainLayout->addWidget(pushButton);
    mainLayout->addWidget(graphicsView);

    this->setLayout(mainLayout);

    graphicsView->setBackgroundBrush( QColor(40, 40, 40) );
    graphicsView->setRenderHint(QPainter::Antialiasing); // Подключаем сглаживание
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate); //Задаем режим перерисовки


    scene = new Scene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // динамическая сцена

    graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, graphicsView->width(), graphicsView->height());


    frameTimer = new QTimer();
    connect(frameTimer, SIGNAL(timeout()),
            scene, SLOT(advance()));
    frameTimer->start(1000/FPS);
}

Widget::~Widget()
{
    delete scene;
    delete ui;
}

void Widget::pushButtonClick()
{
    scene->clearAll();

    for(int i = 0; i < random(minCircles, maxCircles); i++)
        scene->addCircle();
}

void Widget::clearButtonClick()
{
    scene->clearAll();
}

