#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include "myview.h"
#include <controlwidget.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();



private:
    Ui::Widget *ui;

    QGraphicsScene *scene;
    MyView *view;
    ControlWidget *controlPane;
    QHBoxLayout *layout;
    QImage *img;


};

#endif // WIDGET_H
