#include "widget.h"
#include "ui_widget.h"
#include <cmath>
#include <complex>
#include <QtDebug>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QTimer>

#define START_X 0
#define START_Y 0
#define POWER 2
#define START_RANGE 10
#define START_ZOOM_FACTOR 5
#define START_MAX_ITER 100
#define BOUND 4

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->showMaximized();

    layout = new QHBoxLayout(this);
    view = new MyView(this->width(), this->height(), START_X, START_Y, POWER, START_RANGE, START_ZOOM_FACTOR, START_MAX_ITER, BOUND);
    view->setParent(this);
    view->show();

    controlPane = new ControlWidget(this->width() / 5, this);
    controlPane->setProperties(START_X, START_Y, START_MAX_ITER, START_RANGE, START_ZOOM_FACTOR);

    connect(view, SIGNAL(positionChanged(QPointF, double)), controlPane, SLOT(onPositionChange(QPointF, double)));
    connect(controlPane, SIGNAL(updateClicked(double,double,double,int,double)), view, SLOT(onUpdate(double,double,double,int,double)));

    layout->addWidget(view);
    layout->addWidget(controlPane);

    //complex<double> c(1.0, 1.0);
    //QMessageBox::information(this, "E", QString::number(pow(c, 0.5).real()));

    QTimer::singleShot(500, view, SLOT(draw()));
}

Widget::~Widget()
{
    delete ui;
}



