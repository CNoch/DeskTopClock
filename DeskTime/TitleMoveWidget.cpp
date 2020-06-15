#include "TitleMoveWidget.h"
#include <QPainter>
#include <QStyleOption>

TitleMoveWidget::TitleMoveWidget(int height, const QString &style, QWidget *parent) : QWidget(parent)
{
    setFixedSize(parent->width(), height);
    move(parent->x(),parent->y());
    setStyleSheet(style);
}

void TitleMoveWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QWidget *parentWidget = this->parentWidget();
        QPoint point = parentWidget->pos();
        point.setX(point.x() + event->x() - m_PressPoint.x());
        point.setY(point.x() + event->y() - m_PressPoint.y());
        parentWidget->move(point);
    }
}

void TitleMoveWidget::mousePressEvent(QMouseEvent *event)
{
    m_PressPoint = event->pos();
}

void TitleMoveWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}
