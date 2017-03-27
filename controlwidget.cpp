#include <QSpacerItem>
#include <QMessageBox>
#include "controlwidget.h"

ControlWidget::ControlWidget(int width, QWidget *parent) : QWidget(parent)
{
    this->setMaximumWidth(width);

    mainLayout = new QGridLayout(this);
    mainLayout->setColumnMinimumWidth(0, width / 3);

    for(int i = 1; i < 9; i++)
        mainLayout->setRowMinimumHeight(i
                                        , 35);

    labelX = new QLabel("X:");
    labelY = new QLabel("Y:");
    labelIter = new QLabel("Max iterations:");
    labelZoom = new QLabel("Zoom:");
    labelZoomFactor = new QLabel("Zoom factor:");
    editX = new QLineEdit();
    editY = new QLineEdit();
    editIter = new QLineEdit();
    editZoom = new QLineEdit();
    editZoomFactor = new QLineEdit();

    buttonUpdate = new QPushButton("Update");
    buttonZoomIn = new QPushButton("Zoom in");
    buttonZoomOut = new QPushButton("Zoom out");
    buttonHelp = new QPushButton("Help");

    connect(buttonUpdate, &QPushButton::clicked, [&]()
    {
        double x = this->editX->text().toDouble();
        double y = this->editY->text().toDouble();
        double zoom = this->editZoom->text().toDouble();
        int iter = this->editIter->text().toInt();
        double factor = this->editZoomFactor->text().toDouble();
//        QMessageBox::warning(this, "LMBDA",QString::number(x) + "\n" + QString::number(y) + "\n" + QString::number(zoom) + "\n" +
//                             QString::number(iter) + "\n" + QString::number(factor));
        emit updateClicked(x, y, zoom, iter, factor);
    });

    mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 0, 1, 2);

    mainLayout->addWidget(labelX, 1, 0);
    mainLayout->addWidget(editX, 1, 1);
    mainLayout->addWidget(labelY, 2, 0);
    mainLayout->addWidget(editY, 2, 1);
    mainLayout->addWidget(labelIter, 3, 0);
    mainLayout->addWidget(editIter, 3, 1);
    mainLayout->addWidget(labelZoom, 4, 0);
    mainLayout->addWidget(editZoom, 4, 1);
    mainLayout->addWidget(labelZoomFactor, 5, 0);
    mainLayout->addWidget(editZoomFactor, 5, 1);

    mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), 6, 0, 1, 2);

    mainLayout->addWidget(buttonUpdate, 7, 0, 1, 2);
    mainLayout->addWidget(buttonZoomIn, 8, 0, 1, 2);
    mainLayout->addWidget(buttonZoomOut, 9, 0, 1, 2);

    mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), 10, 0, 1, 2);
    mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), 11, 0, 1, 2);
    mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), 12, 0, 1, 2);
    mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), 13, 0, 1, 2);
    mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), 14, 0, 1, 2);

}

void ControlWidget::setProperties(double x, double y, int iter, double zoom, double zoomFactor)
{
    editX->setText(QString::number(x));
    editY->setText(QString::number(y));
    editZoom->setText(QString::number(zoom));
    editIter->setText(QString::number(iter));
    editZoomFactor->setText(QString::number(zoomFactor));
}

void ControlWidget::onPositionChange(QPointF pos, double range)
{
    editX->setText(QString::number(pos.x()));
    editY->setText(QString::number(pos.y()));
    editZoom->setText(QString::number(range));
}
