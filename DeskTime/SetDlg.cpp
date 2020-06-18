#include "SetDlg.h"
#include "ui_SetDlg.h"
#include <qfontdialog.h>
#include <qcolordialog.h>
#include <qlineedit.h>


SetDlg::SetDlg(xml_strcut* xml, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SetDlg),
    m_xml(xml)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    m_TitleMoveWidget = new TitleMoveWidget(30,"",this);
    InitWidget();
}

SetDlg::~SetDlg()
{
    delete ui;
}

void SetDlg::on_pushButton_save_clicked()
{
    //m_xml->TimeType = ui->comboBox_timetype->currentText();
}

void SetDlg::on_pushButton_close_clicked()
{
    m_xml->TimeType = ui->comboBox_timetype->currentText();
    done(1);
}

void SetDlg::on_pushButton_font_clicked()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, QFont(m_xml->font.family,m_xml->font.pointsize,m_xml->font.weight,m_xml->font.italic), this);
    if (ok)
    {
        m_xml->font.family = font.family();
        m_xml->font.pointsize = font.pointSize();
        m_xml->font.weight = font.weight();
        m_xml->font.italic = font.italic();
        ui->lineEdit_font->setText(m_xml->font.family);
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
        ui->lineEdit_font_rgb->setText(QString("%1,%2,%3").arg(m_xml->font.red).arg(m_xml->font.green).arg(m_xml->font.blue));
    }
}

void SetDlg::InitWidget()
{
    ui->lineEdit_font->setText(m_xml->font.family);
    ui->lineEdit_font_color->setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(m_xml->font.red).arg(m_xml->font.green).arg(m_xml->font.blue));
    ui->lineEdit_font_rgb->setText(QString("%1,%2,%3").arg(m_xml->font.red).arg(m_xml->font.green).arg(m_xml->font.blue));

    ui->lineEdit_background_color->setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(m_xml->background.red).arg(m_xml->background.green).arg(m_xml->background.blue));
    ui->lineEdit_background_rgb->setText(QString("%1,%2,%3").arg(m_xml->background.red).arg(m_xml->background.green).arg(m_xml->background.blue));
    ui->horizontalSlider_background_alpha->setValue(m_xml->background.alpha);

    for (int i = 0; i < ui->comboBox_timetype->count(); ++i) {
        if (ui->comboBox_timetype->itemText(i) == m_xml->TimeType)
        {
            ui->comboBox_timetype->setCurrentIndex(i);
        }
    }
}

void SetDlg::on_pushButton_background_color_clicked()
{
    QColor color = QColorDialog::getColor(QColor(m_xml->background.red,m_xml->background.green,m_xml->background.blue));
    if (color.isValid())
    {
        m_xml->background.red = color.red();
        m_xml->background.green = color.green();
        m_xml->background.blue = color.blue();
        ui->lineEdit_background_color->setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(m_xml->background.red).arg(m_xml->background.green).arg(m_xml->background.blue));
        ui->lineEdit_background_rgb->setText(QString("%1,%2,%3").arg(m_xml->background.red).arg(m_xml->background.green).arg(m_xml->background.blue));
    }
}

void SetDlg::on_comboBox_timetype_currentIndexChanged(const QString &arg1)
{
    m_xml->TimeType = arg1;
}

void SetDlg::on_horizontalSlider_background_alpha_valueChanged(int value)
{
    m_xml->background.alpha = value;
}
