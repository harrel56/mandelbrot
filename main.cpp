#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	//Run app
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
