#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(int width, QWidget *parent = 0);

    void setProperties(double x, double y, int iter, double zoom, double zoomFactor);

    QPushButton *buttonUpdate;
    QPushButton *buttonZoomIn;
    QPushButton *buttonZoomOut;
    QPushButton *buttonHelp;

private:
    QLabel *labelX;
    QLabel *labelY;
    QLabel *labelIter;
    QLabel *labelZoom;
    QLabel *labelZoomFactor;

    QLineEdit *editX;
    QLineEdit *editY;
    QLineEdit *editIter;
    QLineEdit *editZoom;
    QLineEdit *editZoomFactor;



    QGridLayout *mainLayout;

signals:
    void updateClicked(double x, double y, double range, int maxIter, double zoom);

public slots:
    void onPositionChange(QPointF pos, double range);
};

#endif // CONTROLWIDGET_H
