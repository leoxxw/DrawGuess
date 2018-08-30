#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatwidget.h"
#include <QTcpSocket>
#include <QHostAddress>
#include "loginwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool getSetting();
    void connectSer();

private slots:
    void slotconnectedsuccess();//用来处理连接成功的信号
    void slotreceive();//接收服务器传过来的信息
    void slotSendMsg(QString msg);//消息传输
    void slot_login(QString user);//登录

private:
    Ui::MainWindow *ui;
    loginwidget* m_loginWidget;
    ChatWidget* m_chatWidget;
    int port;
    QHostAddress *serverIP;
    QString userName;
    QTcpSocket *tcpsocket;
};

#endif // MAINWINDOW_H
