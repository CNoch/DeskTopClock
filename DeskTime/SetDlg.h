#ifndef SETDLG_H
#define SETDLG_H

#include <QWidget>

namespace Ui {
class SetDlg;
}

class SetDlg : public QWidget
{
    Q_OBJECT

public:
    explicit SetDlg(QWidget *parent = nullptr);
    ~SetDlg();

private:
    Ui::SetDlg *ui;
};

#endif // SETDLG_H
