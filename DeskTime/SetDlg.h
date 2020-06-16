#ifndef SETDLG_H
#define SETDLG_H

#include <QDialog>
#include "TitleMoveWidget.h"
#include "define.h"

namespace Ui {
class SetDlg;
}

class SetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SetDlg(xml_strcut *xml,QWidget *parent = nullptr);
    ~SetDlg();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_font_clicked();

    void on_pushButton_font_color_clicked();

private:
    Ui::SetDlg *ui;
    TitleMoveWidget *m_TitleMoveWidget;
    xml_strcut* m_xml;
};

#endif // SETDLG_H
