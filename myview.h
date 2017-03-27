#ifndef MYVIEW_H
#define MYVIEW_H

#include <cmath>
#include <complex>

#include <QGraphicsView>
#include <QMouseEvent>
#include <QList>
#include <QColor>


class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    MyView(int x, int y, double posX, double posY, double power, double range, double zoom, int maxIter, int bound);

    double getModulus(double x, double y);
    double getModulus(QPointF p);
    QPointF getSquare(double re, double im);
    QPointF getSquare(QPointF p);
    QPointF getNumOfIterations(double x, double y, int maxIter = 100, double power = 2.0, double bound = 4.0);

public slots:
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *e);

    void draw(double ptX = 0 , double ptY = 0, double range = 10);

    void onUpdate(double x, double y, double range, int maxIter, double zoom);

signals:
    void positionChanged(QPointF pos, double zoom);

private:

    double h;
    double ptX;
    double ptY;
    double range;
    double power;
    double zoom;
    double bound;
    int minIter;
    int maxIter;
    QGraphicsTextItem *text;
    QGraphicsScene *scene;
    QImage *img;
    QList<QColor> colors;
};

#endif // MYVIEW_H
