#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>
#include <QPainter>
#include <windows.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    //this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //m_TitleMoveWidget = new TitleMoveWidget();
    m_Timer = new QTimer(this);
    connect(m_Timer,&QTimer::timeout,this,&Widget::on_timeout);
    m_Timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(this->rect(),QColor(0,0,0,50));
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && m_InitialPoint_bool && m_Move_flag)
    {
        QPoint point = this->pos();
        point.setX(point.x() + event->x() - m_InitialPoint.x());
        point.setY(point.y() + event->y() - m_InitialPoint.y());
        this->move(point);
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    m_InitialPoint = event->pos();
    m_InitialPoint_bool = true;
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    m_InitialPoint_bool = false;
}

void Widget::on_timeout()
{
    ui->label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}


void Widget::on_pushButton_2_clicked()
{
    m_Move_flag = !m_Move_flag;
    if (m_Move_flag)
    {
        ui->pushButton_2->setText(QStringLiteral("固定"));
    }
    else {
        ui->pushButton_2->setText(QStringLiteral("取消固定"));
    }
}

void Widget::on_pushButton_clicked()
{
    m_Top_flag = !m_Top_flag;
    if (m_Top_flag)
    {
        ui->pushButton->setText(QStringLiteral("取消置顶"));
        ::SetWindowPos(HWND(this->winId()),HWND_TOPMOST,0,0,0,0,SWP_NOMOVE| SWP_NOSIZE | SWP_SHOWWINDOW);
    }
    else {
        ui->pushButton->setText(QStringLiteral("置顶"));
        ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }
}
