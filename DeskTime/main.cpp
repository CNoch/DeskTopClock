#include "widget.h"

#include <QApplication>
#include <qwidget.h>
#include <QPaintEvent>
#include <QPainter>

//测试
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
