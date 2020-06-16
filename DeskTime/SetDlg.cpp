#include "SetDlg.h"
#include "ui_SetDlg.h"

SetDlg::SetDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDlg)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    m_TitleMoveWidget = new TitleMoveWidget(30,"",this);
    ui->pushButton_close->raise();
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

}
