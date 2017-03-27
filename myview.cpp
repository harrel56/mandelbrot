#include <conio.h>
#include <limits.h>
#include <cmath>
#include <complex>
#include "myview.h"

#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QGraphicsPixmapItem>
#include <QTime>
#include <QElapsedTimer>

using namespace std;

MyView::MyView(int x, int y, double posX, double posY, double power, double range, double zoom, int maxIter, int bound)
{
    this->resize(x, y);
    scene = new QGraphicsScene(0, 0, x, y);
    img = new QImage(scene->width(), scene->height(), QImage::Format_ARGB32);
    text = new QGraphicsTextItem();
    text->setPos(10, 10);
    minIter = INT_MAX;
    this->power = power;
    this->range = range;
    this->zoom = zoom;
    this->maxIter = maxIter;
    this->bound = bound;

    this->setScene(scene);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::HighQualityAntialiasing);

    QImage grad(QCoreApplication::applicationDirPath() + "/grad3.png");

    for(int i = 0; i < grad.width(); i++)
    {
        colors.append(grad.pixelColor(i, 0));
    }

    //this->draw(posX, posY, this->range);

}

void MyView::draw(double ptX, double ptY, double range)
{

    this->range = range;
    this->ptX = ptX;
    this->ptY = ptY;
    h = range / scene->width();
    double startX = ptX - h * scene->width() / 2.0;
    double endX = ptX - h + h * scene->width() / 2.0;
    double startY = ptY + h * scene->height() / 2.0;
    double endY = ptY + h - h * scene->height() / 2.0;

//    qDebug() << "h = " << h;
//    qDebug() << "sY = " << startY;
//    qDebug() << "eY = " << endY;
//    qDebug() << "sX = " << startX;
//    qDebug() << "eX = " << endX;
//    qDebug() << "iterY = " << (startY - endY)/h;
//    qDebug() << "iterX = " << (endX - startX)/h;

    delete img;
    img = new QImage(scene->width(), scene->height(), QImage::Format_ARGB32);
    img->fill(qRgba(0, 0, 0, 0));

    uchar *bits = img->bits();

    int pointer = 0;
    QPointF iter;
    double x = startX + h/2;
    double y = startY - h/2;
    int prevMinIter;
    if(minIter == INT_MAX)
    {
        prevMinIter = 0;
    }
    else
    {
        prevMinIter = minIter;
        minIter = INT_MAX;
    }
    for(int he = 0; he < img->size().height(); he++)
    {
        x = startX;
        for(int wi = 0; wi < img->size().width(); wi++)
        {

            iter = getNumOfIterations(x, y, prevMinIter + maxIter, this->power, this->bound);
            if(minIter > iter.x() && iter.x() >= 0)
                minIter = iter.x();
            if(iter.x() == -1)
            {
                bits[pointer] = 0;
                pointer++;
                bits[pointer] = 0;
                pointer++;
                bits[pointer] = 0;
                pointer++;
                bits[pointer] = 255;
                pointer++;
            }
            else
            {
                //int ind = (iter.x() - prevMinIter) - log2(log(iter.y()) / log(4));
                int ind = (iter.x() - prevMinIter);
                bits[pointer] = colors[ind % colors.size()].blue();
                pointer++;
                bits[pointer] = colors[ind % colors.size()].green();
                pointer++;
                bits[pointer] = colors[ind % colors.size()].red();
                pointer++;
                bits[pointer] = 255;
                pointer++;
            }
            x += h;
            //if(iter > 250)
            //    qDebug() << "OVER 250";
        }
        //QMessageBox::information(nullptr, "E", "cnt = " + QString::number(counter));
        if(he % 200 == 0)
        {
            scene->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(*img)));
            QCoreApplication::processEvents();
        }
        qDebug() << "he = " << he;
        y -= h;
    }

    scene->clear();
    scene->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(*img)));

}

void MyView::mousePressEvent(QMouseEvent *event)
{
    double realX = (ptX - h * scene->width() / 2.0) + (event->x() * h);
    double realY = (ptY + h * scene->height() / 2.0) - (event->y() * h);
    //QMessageBox::information(nullptr, "CLICK", "x = " + QString::number(realX) + "\nY = " + QString::number(realY));
    emit positionChanged(QPointF(realX, realY), range / zoom);
    draw(realX, realY, range / zoom);
}

void MyView::resizeEvent(QResizeEvent *e)
{
    scene->setSceneRect(0, 0, e->size().width(), e->size().height());
}

double MyView::getModulus(double x, double y)
{
    return sqrt(x*x + y*y);
}

double MyView::getModulus(QPointF p)
{
    return sqrt(p.x()*p.x() + p.y()*p.y());
}

QPointF MyView::getSquare(double re, double im)
{
    return QPointF(re*re - im*im, 2 * im*re);
}

QPointF MyView::getSquare(QPointF p)
{
    return QPointF(p.x()*p.x() - p.y()*p.y(), 2 * p.x()*p.y());
}

QPointF MyView::getNumOfIterations(double x, double y, int maxIter, double power, double bound)
{
    double cx = x;
    double cy = y;
    double zx = 0;
    double zy = 0;

    for(int i = 0; i < maxIter; i++)
    {

        if(zx*zx + zy*zy >= bound)
            return QPointF(i, getModulus(zx, zy));

        double tx = zx;
        zx = zx*zx - zy*zy + cx;
        zy = 2 * tx*zy + cy;

    }
    return QPointF(-1, -1);
}

void MyView::onUpdate(double x, double y, double range, int maxIter, double zoom)
{
    this->maxIter = maxIter;
    this->zoom = zoom;

    draw(x, y, range);
}
