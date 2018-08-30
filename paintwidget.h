#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
#include <QWidget>

//选择画特殊图型的类型
enum shape
{
    Line=0,
    Rect,
    Ellipse,
    Pen,
    Erase
};

class paintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit paintWidget(QWidget *parent = 0);//构造函数
    void paint(QImage &theimage);

    void paintEx(int type, QPoint lastPoint, QPoint endPoint);

    void setbPaint(bool b);


protected:
     void mousePressEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void paintEvent(QPaintEvent *event);

public:
    void setCurrentShape(shape t);
    void setPenSize(int size);
    void setPenColor(QColor color);
    void setClear();
signals:
    void signal_paint(shape type, QPoint lastPoint,QPoint endPoint);

private:
    bool bpaint;
    bool drawing;
    QImage image;
    QImage tempImage;
    shape type;
    QColor setting_color;
    QColor penColor;
    QPoint  lastPoint;
    QPoint endPoint;
    int nSize;
};

#endif // PAINTWIDGET_H
