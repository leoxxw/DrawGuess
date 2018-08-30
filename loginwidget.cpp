#include "loginwidget.h"
#include "ui_loginwidget.h"

loginwidget::loginwidget(BaseMainWidget *parent) :
    BaseMainWidget(parent),
    ui(new Ui::loginwidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
}

loginwidget::~loginwidget()
{
    delete ui;
}

void loginwidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Return://数字键盘的Enter键
    case Qt::Key_Enter://Enter键
        on_pushButton_login_clicked();
        break;
    default:
        break;
    }
}

void loginwidget::on_pushButton_login_clicked()
{
    QString user = ui->lineEdit_user->text();
    if(user.isEmpty())
    {
        return;
    }
    emit signals_login(user);
}

void loginwidget::on_pushButton_min_clicked()
{
    this->showMinimized();
}

void loginwidget::on_pushButton_clo_clicked()
{
    this->close();
}
