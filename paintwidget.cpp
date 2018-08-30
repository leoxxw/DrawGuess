#include "paintwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPainter>


paintWidget::paintWidget(QWidget *parent):
    QWidget(parent),
    nSize(2),
    bpaint(true)
{
    drawing=false;//表明未开始画图时,用于双缓冲
    type = Pen;//默认选择画线
    image = QImage(1900,600,QImage::Format_RGB32);//设定一张采用32位图（最常用的）的规模为900*600的画布
    setting_color = qRgb(255,255,255);//选定背景色为白色
    penColor = qRgb(0,0,0);//黑色
    image.fill(setting_color);//将背景色填充在画布上
    tempImage = image;
}

void paintWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    if(drawing == true){
        painter.drawImage(0,0,tempImage);//在正在画图时（鼠标开始点击但按住拖动过程）画在临时画布
    }
    else{
        painter.drawImage(0,0,image);//当鼠标松开后,把图形画在画布上
    }
}

void paintWidget::setCurrentShape(shape t)
{
    if(t != type)
    {
        type = t;
    }
}

void paintWidget::setPenSize(int size)
{
    nSize = size;
}

void paintWidget::setPenColor(QColor color)
{
    penColor = color;
}

void paintWidget::setClear()
{
    image.fill(setting_color);//将背景色填充在画布上
    update();
}
void paintWidget::mousePressEvent(QMouseEvent *event)
{
    if(!bpaint)
    {
        return;
    }
    if(event->button()==Qt::LeftButton){//判断是否按住鼠标左键
        lastPoint=event->pos();

        drawing = true;//正在画图
    }
}

void paintWidget::mouseMoveEvent(QMouseEvent *event)
{

    if(!bpaint)
    {
        return;
    }
    if(event->buttons()&Qt::LeftButton){//当满足按住并且拖动鼠标左键时
        endPoint=event->pos();//把鼠标所在位置的坐标传给后一个点
        tempImage = image;
        if(type == Pen || type == Erase){
            paint(image);//若工具为画笔无需双缓冲
        }
        else{
            paint(tempImage);//双缓冲绘图
        }
    }
}

void paintWidget::mouseReleaseEvent(QMouseEvent *event)
{

    if(!bpaint)
    {
        return;
    }
    if(event->button()==Qt::LeftButton){//判断是否按住鼠标左键
        endPoint=event->pos();//
        drawing=false;//停止绘画
        if(type != Pen){
            paint(image);
        }
    }
}

void paintWidget::paint(QImage &theimage)
{
    if(bpaint)
    {
        if(type == Line ||type == Rect ||type == Ellipse)
        {
            if(!drawing)
            {
              emit signal_paint(type,lastPoint,endPoint);
            }
        }else{
            emit signal_paint(type,lastPoint,endPoint);
        }

    }

    QPainter p(&theimage);//draw on the image
    QPen pen = QPen();//选用一支笔
    pen.setWidth(nSize);//设定画笔粗度
    pen.setColor(penColor);
    p.setPen(pen);//设定画图工具为一支笔

    QRect rect;
    switch (type) {
    case Line:{
        p.drawLine(lastPoint,endPoint);
        break;
    }

    case Rect:{
        p.drawRect(lastPoint.x(),lastPoint.y(),endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());
        //有必要说一下画矩形，大家都知道要确定两个顶点即可，这里就是这个意思。至于函数大家可以F1看一下
        break;
    }
    case Ellipse:{
        p.drawEllipse(lastPoint.x(),lastPoint.y(),endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());
        //方法同画矩形，不再赘述
        break;
    }
    case Pen:{//也就是上一讲的涂鸦
        p.drawLine(lastPoint,endPoint);//用画图工具画线
        lastPoint=endPoint;
        break;
    }
    case Erase:{//也就是上一讲的涂鸦
        rect=QRect(lastPoint,QPoint(lastPoint.x()+10,lastPoint.y()+10));  //橡皮擦大小
        p.eraseRect(rect);
        lastPoint=endPoint;
        break;
    }
    default:
        break;
    }

    update();//进行更新界面显示，可引起窗口重绘事件,不再赘述

}

void paintWidget::paintEx(int type, QPoint lastPoint, QPoint endPoint)
{
    bpaint = false;
    this->type =(shape)type;
    this->lastPoint = lastPoint;
    this->endPoint = endPoint;
    paint(image);
}

void paintWidget::setbPaint(bool b)
{
    bpaint = b;
}

