#ifndef TITLEMOVEWIDGET_H
#define TITLEMOVEWIDGET_H
//提供移动窗口的标题栏 2020/06/09 10:00:00

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>

class TitleMoveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleMoveWidget(int height = 30, const QString &style = nullptr, QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
signals:

private:
    QPoint m_PressPoint;
};

#endif // TITLEMOVEWIDGET_H
