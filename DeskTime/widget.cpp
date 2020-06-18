#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>
#include <QPainter>
#include <QAction>
#include <QIcon>
#include <QApplication>
#include <QSettings>
#ifdef Q_OS_WIN
#include <windows.h>
#define Regedit_User "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
#define Regedit_Admin ""
#else
#endif

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

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
                    QString name = reader.name().toString();
                    if ("x" == name)
                    {
                        xml->x = reader.readElementText().toInt();
                    }
                    else if ("y" == name)
                    {
                        xml->y = reader.readElementText().toInt();
                    }
                    else if ("width" == name)
                    {
                        xml->width = reader.readElementText().toInt();
                    }
                    else if ("height" == name)
                    {
                        xml->height = reader.readElementText().toInt();
                    }
                    else if ("boot" == name)
                    {
                        xml->boot = reader.readElementText().toInt();
                    }
                    else if ("top" == name)
                    {
                        xml->top = reader.readElementText().toInt();
                    }
                    else if ("fixed" == name)
                    {
                        xml->fixed = reader.readElementText().toInt();
                    }
                    else if ("font" == name)
                    {
                        xml->font.family = reader.attributes().value("family").toString();
                        xml->font.pointsize = reader.attributes().value("pointsize").toInt();
                        xml->font.weight = reader.attributes().value("weight").toInt();
                        xml->font.italic = reader.attributes().value("italic").toInt();
                        xml->font.red = reader.attributes().value("red").toInt();
                        xml->font.green = reader.attributes().value("green").toInt();
                        xml->font.blue = reader.attributes().value("blue").toInt();
                    }
                    else if ("timetype" == name)
                    {
                        xml->TimeType = reader.readElementText();
                    }
                    else if ("background" == name)
                    {
                        xml->background.red = reader.attributes().value("red").toInt();
                        xml->background.green = reader.attributes().value("green").toInt();
                        xml->background.blue = reader.attributes().value("blue").toInt();
                        xml->background.alpha = reader.attributes().value("alpha").toInt();
                    }
                    break;
                }
                }
            }
            file.close();
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
            writer.writeTextElement("boot",QString("%1").arg(xml.boot));
            writer.writeTextElement("top",QString("%1").arg(xml.top));
            writer.writeTextElement("fixed",QString("%1").arg(xml.fixed));

            writer.writeStartElement("font");
            QXmlStreamAttributes butes;
            butes.append("family",xml.font.family);
            butes.append("pointsize",QString("%1").arg(xml.font.pointsize));
            butes.append("wdight",QString("%1").arg(xml.font.weight));
            butes.append("italic",QString("%1").arg(xml.font.italic));
            butes.append("red",QString("%1").arg(xml.font.red));
            butes.append("green",QString("%1").arg(xml.font.green));
            butes.append("blue",QString("%1").arg(xml.font.blue));
            writer.writeAttributes(butes);
            writer.writeEndElement();

            writer.writeTextElement("timetype",xml.TimeType);

            writer.writeStartElement("background");
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

#ifdef Q_OS_WIN
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::SubWindow);
    this->setAttribute(Qt::WA_QuitOnClose,true);
#else
    this->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
#endif // Q_OS_LINUX


    this->setAttribute(Qt::WA_TranslucentBackground);

    m_Timer = new QTimer(this);
    connect(m_Timer,&QTimer::timeout,this,&Widget::on_timeout);
    m_Timer->start(1000);

    //xml_path
    QString xml_path = QApplication::applicationDirPath() + "/AppInfo.xml";
    m_Xml_Helper = new Xml_Helper(xml_path,this);

    m_Xml_Helper->read(&m_xml);
    InitWidget();
}

Widget::~Widget()
{
    //on_save_config();
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(this->rect(), QColor(m_xml.background.red, m_xml.background.green, m_xml.background.blue, m_xml.background.alpha));
    //ui->label->setFont(QFont(m_xml.font.family,m_xml.font.pointsize,m_xml.font.weight,m_xml.font.italic));
    //ui->label->setStyleSheet(QString("color:rgb(%1,%2,%3)").arg(m_xml.font.red).arg(m_xml.font.green).arg(m_xml.font.blue));
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && m_InitialPoint_bool && !m_Fixed_flag)
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
    ui->label->setText(QDateTime::currentDateTime().toString(m_xml.TimeType));
}


void Widget::on_action_fixed_clicked()
{
    m_Fixed_flag = !m_Fixed_flag;
    QAction *action_fixed = m_Menu->actions().at(0);
    if (!m_Fixed_flag)
    {
        action_fixed->setIcon(QIcon(QStringLiteral(":/img/nail.png")));
    }
    else
    {
        action_fixed->setIcon(QIcon(QStringLiteral(":/img/nail_fixed.png")));
    }
}

void Widget::on_action_set_clicked()
{
    xml_strcut xml = m_xml;
    if (m_SetDlg == nullptr)
        m_SetDlg = new SetDlg(&xml,this);
    switch (m_SetDlg->exec()) {
    case 1:
    {
        m_xml = xml;
        ui->label->setFont(QFont(m_xml.font.family,m_xml.font.pointsize,m_xml.font.weight,m_xml.font.italic));
        ui->label->setStyleSheet(QString("color:rgb(%1,%2,%3)").arg(m_xml.font.red).arg(m_xml.font.green).arg(m_xml.font.blue));
        //update();
        break;
    }
    }
}

#ifdef Q_OS_WIN
void Widget::on_action_boot_clicked()
{
    m_Boot_flag = !m_Boot_flag;
    setBoot();
}

void Widget::on_action_top_clicked()
{
    m_Top_flag = !m_Top_flag;
    setTop();
}
#endif

void Widget::on_action_save_clicked()
{
    m_xml.x = this->pos().x();
    m_xml.y = this->pos().y();
    m_xml.top = m_Top_flag;
    m_xml.fixed = m_Fixed_flag;
    m_xml.boot = m_Boot_flag;
    m_Xml_Helper->write(m_xml);
}


void Widget::on_label_customContextMenuRequested(const QPoint &pos)
{
    m_Menu->exec(QCursor::pos());
}

void Widget::InitWidget()
{
    this->move(m_xml.x,m_xml.y);
    m_Fixed_flag = m_xml.fixed == 0 ? false : true;
    m_Top_flag = m_xml.top == 0 ? false : true;
    m_Boot_flag = m_xml.boot == 0 ? false : true;
    ui->label->setFont(QFont(m_xml.font.family,m_xml.font.pointsize,m_xml.font.weight,m_xml.font.italic));
    ui->label->setStyleSheet(QString("color:rgb(%1,%2,%3)").arg(m_xml.font.red).arg(m_xml.font.green).arg(m_xml.font.blue));
    InitMenu();
}

void Widget::InitMenu()
{
    m_Menu = new QMenu(this);
    //Fixed
    QAction *action_fixed = new QAction(QIcon(m_Fixed_flag ? QStringLiteral(":/img/nail_fixed.png") : QStringLiteral(":/img/nail.png")),QStringLiteral("Fixed"),this);
    connect(action_fixed,&QAction::triggered,this,&Widget::on_action_fixed_clicked);
    m_Menu->addAction(action_fixed);

    //Set
    QAction *action_set = new QAction(QIcon(QStringLiteral(":/img/set.png")),QStringLiteral("Set"),this);
    connect(action_set,&QAction::triggered,this,&Widget::on_action_set_clicked);
    m_Menu->addAction(action_set);

    //Save
    QAction* action_save = new QAction(QIcon(QStringLiteral(":/img/save.png")), QStringLiteral("Save"), this);
    connect(action_save, &QAction::triggered, this, &Widget::on_action_save_clicked);
    m_Menu->addAction(action_save);
    //Top
#ifdef Q_OS_WIN
    //Boot
    QAction *action_boot = new QAction(QStringLiteral("Boot"),this);
    connect(action_boot,&QAction::triggered,this,&Widget::on_action_boot_clicked);
    m_Menu->addAction(action_boot);

    QAction *action_top = new QAction(QStringLiteral("Top"),this);
    
    connect(action_top,&QAction::triggered,this,&Widget::on_action_top_clicked);
    m_Menu->addAction(action_top);
#endif
    m_Menu->addSeparator();
    //close
    QAction* action_close = new QAction(QIcon(QStringLiteral(":/img/quit.png")), QStringLiteral("Quit"), this);
    connect(action_close, &QAction::triggered, [this]() {this->close(); });
    m_Menu->addAction(action_close);

#ifdef Q_OS_WIN
    setTop();
    setBoot();
#endif // Q_OS_WIN


}

#ifdef Q_OS_WIN
void Widget::setBoot()
{
    QAction* acton_boot = m_Menu->actions().at(m_Menu->actions().size() - 4);
    if (m_Boot_flag)
    {
        acton_boot->setIcon(QIcon(QString(":/img/boot_2.png")));
    }
    else
    {
        acton_boot->setIcon(QIcon(QString(":/img/boot_1.png")));
    }


    if (m_Boot_flag)
    {
        QString app_path = QApplication::applicationDirPath() + "/DeskTime.exe";
        app_path = app_path.replace("/", "\\");
        QSettings set(Regedit_User, QSettings::NativeFormat);
        set.setValue("CQ_DESKTIME", app_path);
    }
    else
    {
        QSettings set(Regedit_User, QSettings::NativeFormat);
        set.remove("CQ_DESKTIME");
    }
}

void Widget::setTop()
{
    QAction* action_top = m_Menu->actions().at(m_Menu->actions().size() - 3);
    if (m_Top_flag)
    {
        action_top->setIcon(QIcon(QStringLiteral(":/img/top_2.png")));
        ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }
    else {
        action_top->setIcon(QIcon(QStringLiteral(":/img/top_1.png")));
        ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }
}
#endif // Q_OS_WIN


