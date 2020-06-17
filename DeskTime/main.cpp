#include "widget.h"

#include <QApplication>
#include <qwidget.h>
#include <QPaintEvent>
#include <QPainter.h>

class hide_widget : public QWidget
{
public:
	hide_widget(QWidget *parent = nullptr);
	~hide_widget();

private:

protected:
    void paintEvent(QPaintEvent* event);

};

hide_widget::hide_widget(QWidget* parent)
    :QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
}

hide_widget::~hide_widget()
{
}

void hide_widget::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.fillRect(this->rect(), QColor(0,0,0,0));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hide_widget hide;
    Widget w(&hide);
    w.show();
    return a.exec();
}
