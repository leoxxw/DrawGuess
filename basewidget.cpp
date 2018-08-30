#include "basewidget.h"
#include "ui_basewidget.h"

BaseWidget::BaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseWidget)
{
    ui->setupUi(this);
}

BaseWidget::~BaseWidget()
{
    delete ui;
}

void BaseWidget::mousePressEvent(QMouseEvent *event)
{
   return;
   QWidget:: mousePressEvent(event);
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event)
{
    return;
    QWidget:: mouseMoveEvent(event);
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    return;
    QWidget:: mouseReleaseEvent(event);
}
