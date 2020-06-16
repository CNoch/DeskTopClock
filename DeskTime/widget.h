#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QMenu>
#include <SetDlg.h>
#include "define.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE



class Xml_Helper;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_timeout();
    void on_action_fixed_clicked();

    void on_action_top_clicked();

    void on_action_set_clicked();

    void on_label_customContextMenuRequested(const QPoint &pos);

private:
    void InitMenu();

private:
    Ui::Widget *ui;
    QTimer *m_Timer = nullptr;
    bool m_Move_flag = true;                //窗口移动
    bool m_InitialPoint_bool = false;       //鼠标点击标志位（用于进行窗口移动）
    QPoint  m_InitialPoint;                 //鼠标点击初始点（用于进行窗口移动）

    bool m_Top_flag = false;                 //窗口置顶

    QMenu *m_Menu;                          //

    SetDlg *m_SetDlg = nullptr;

    xml_strcut m_xml;
    Xml_Helper *m_Xml_Helper;
};
#endif // WIDGET_H
