#ifndef BASEMAINWIDGET_H
#define BASEMAINWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDateTime>

class BaseMainWidget: public QWidget
{
     Q_OBJECT
public:
    BaseMainWidget(QWidget *parent = 0);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    QPoint last;
};

#endif // BASEMAINWIDGET_H
