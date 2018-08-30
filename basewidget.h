#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

namespace Ui {
class BaseWidget;
}

class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseWidget(QWidget *parent = 0);
    ~BaseWidget();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::BaseWidget *ui;
};

#endif // BASEWIDGET_H
