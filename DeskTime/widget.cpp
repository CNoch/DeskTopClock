#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>
#include <QPainter>
#include <QAction>
#include <QIcon>

#ifdef Q_OS_WIN
#include <windows.h>
#eles
#endif

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

struct xml_strcut
{
    int x;
    int y;
    int width;
    int height;
    struct xml_font
    {
        QString font;
        int red;
        int green;
        int blue;
    };
    xml_font font;
    QString TimeType;
    struct xml_background
    {
        int red;
        int green;
        int blue;
        int alpha;
    };
    xml_background background;
};

class Xml_Helper
{
public:
    Xml_Helper(const QString &filepath, QObject *parent = nullptr)
        :m_Filepath(filepath)
    {
    }
    ~Xml_Helper()
    {

    }


    void read(xml_strcut *xml)
    {
        QFile file(m_Filepath);
        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QXmlStreamReader reader(&file);
            while(!reader.atEnd())
            {
                QXmlStreamReader::TokenType token = reader.readNext();
                switch (token) {
                case QXmlStreamReader::StartElement:
                {

                }
                }
            }
        }
    }
    void write(const xml_strcut &xml)
    {
        QFile file(m_Filepath);
        if (file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QXmlStreamWriter writer(&file);
            writer.setAutoFormatting(true);
            writer.setCodec("utf-8");
            writer.writeStartDocument();

            writer.writeStartElement("AppInfo");


            writer.writeTextElement("x",QString("%1").arg(xml.x));
            writer.writeTextElement("y",QString("%1").arg(xml.y));
            writer.writeTextElement("width",QString("%1").arg(xml.width));
            writer.writeTextElement("height",QString("%1").arg(xml.height));

            writer.writeStartElement("Font");
            QXmlStreamAttributes butes;
            butes.append("family",xml.font.font);
            butes.append("red",QString("%1").arg(xml.font.red));
            butes.append("green",QString("%1").arg(xml.font.green));
            butes.append("blue",QString("%1").arg(xml.font.blue));
            writer.writeAttributes(butes);
            writer.writeEndElement();

            writer.writeTextElement("timetype",xml.TimeType);

            writer.writeStartElement("Background");
            butes.clear();
            butes.append("red",QString("%1").arg(xml.background.red));
            butes.append("green",QString("%1").arg(xml.background.green));
            butes.append("blue",QString("%1").arg(xml.background.blue));
            butes.append("alpha",QString("%1").arg(xml.background.alpha));
            writer.writeAttributes(butes);
            writer.writeEndElement();

            writer.writeEndElement();


            writer.writeEndDocument();
            file.close();
        }
    }

private:
    QString m_Filepath;
};


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //m_TitleMoveWidget = new TitleMoveWidget();
    InitMenu();
    m_Timer = new QTimer(this);
    connect(m_Timer,&QTimer::timeout,this,&Widget::on_timeout);
    m_Timer->start(1000);

    m_Xml_Helper = new Xml_Helper("test.xml",this);
    xml_strcut xml;
    m_Xml_Helper->write(xml);
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


void Widget::on_action_fixed_clicked()
{
    m_Move_flag = !m_Move_flag;
    QAction *action_fixed = m_Menu->actions().at(0);
    if (m_Move_flag)
    {
        action_fixed->setIcon(QIcon(QStringLiteral(":/img/钉子_fixed_hover.png")));
    }
    else
    {
        action_fixed->setIcon(QIcon(QStringLiteral(":/img/钉子_fixed.png")));
    }
}
#ifdef Q_OS_WIN
void Widget::on_action_top_clicked()
{
    m_Top_flag = !m_Top_flag;
    QAction *action_top = m_Menu->actions().at(1);
    if (m_Top_flag)
    {
        action_top->setIcon(QIcon(QStringLiteral(":/img/置顶.png")));
        ::SetWindowPos(HWND(this->winId()),HWND_TOPMOST,0,0,0,0,SWP_NOMOVE| SWP_NOSIZE | SWP_SHOWWINDOW);
    }
    else {
        action_top->setIcon(QIcon(QStringLiteral(":/img/置顶 (1).png")));
        ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }
}
#else
void Widget::on_action_top_clicked()
{
    m_Top_flag = !m_Top_flag;
}

void Widget::on_action_set_clicked()
{
    if (m_SetDlg == nullptr)
        m_SetDlg = new SetDlg(this);
    m_SetDlg->exec();
}
#endif

void Widget::on_label_customContextMenuRequested(const QPoint &pos)
{
    m_Menu->exec(QCursor::pos());
}

void Widget::InitMenu()
{
    m_Menu = new QMenu(this);
    //
    QAction *action_fixed = new QAction(QIcon(QStringLiteral(":/img/钉子_fixed_hover.png")),QStringLiteral("固定"),this);
    connect(action_fixed,&QAction::triggered,this,&Widget::on_action_fixed_clicked);
    m_Menu->addAction(action_fixed);

    //置顶
#ifdef Q_OS_WIN
    QAction *action_top = new QAction(QIcon(QStringLiteral(":/img/置顶 (1).png")),QStringLiteral("置顶"),this);
    connect(action_top,&QAction::triggered,this,&Widget::on_action_top_clicked);
    m_Menu->addAction(action_top);
#endif

    //设置
    QAction *action_set = new QAction(QIcon(QStringLiteral(":/img/设置.png")),QStringLiteral("设置"),this);
    connect(action_set,&QAction::triggered,this,&Widget::on_action_set_clicked);
    m_Menu->addAction(action_set);

    m_Menu->addSeparator();
    //close
    QAction *action_close = new QAction(QIcon(QStringLiteral(":/img/关闭 (1).png")),QStringLiteral("退出"),this);
    connect(action_close,&QAction::triggered,[this](){this->close();});
    m_Menu->addAction(action_close);
}
