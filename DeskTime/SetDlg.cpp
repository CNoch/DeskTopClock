#include "SetDlg.h"
#include "ui_SetDlg.h"
#include <qfontdialog.h>
#include <qcolordialog.h>


SetDlg::SetDlg(xml_strcut* xml, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SetDlg),
    m_xml(xml)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    m_TitleMoveWidget = new TitleMoveWidget(30,"",this);

    ui->lineEdit_font->setText(m_xml->font.font);
    ui->lineEdit_font_color->setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(m_xml->font.red).arg(m_xml->font.green).arg(m_xml->font.blue));
}

SetDlg::~SetDlg()
{
    delete ui;
}

void SetDlg::on_pushButton_save_clicked()
{
    //this->close();
}

void SetDlg::on_pushButton_close_clicked()
{
    this->close();
}

void SetDlg::on_pushButton_font_clicked()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, m_xml->font.font, this);
    if (ok)
    {
        m_xml->font.font = font.toString();
        ui->lineEdit_font->setText(m_xml->font.font);
    }
}

void SetDlg::on_pushButton_font_color_clicked()
{
    QColor color = QColorDialog::getColor(QColor(m_xml->font.red, m_xml->font.green, m_xml->font.blue));
    if (color.isValid())
    {
        m_xml->font.red = color.red();
        m_xml->font.green = color.green();
        m_xml->font.blue = color.blue();
        ui->lineEdit_font_color->setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(m_xml->font.red).arg(m_xml->font.green).arg(m_xml->font.blue));
    }
}
