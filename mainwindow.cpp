#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonParseError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_loginWidget(NULL),
    m_chatWidget(NULL)
{
    ui->setupUi(this);
    //获取设置信息
    if(!getSetting())
    {
        return;
    }

    serverIP = new QHostAddress();
    connectSer();

    m_loginWidget = new loginwidget();
    connect(m_loginWidget, &loginwidget::signals_login, this, &MainWindow::slot_login);
    m_loginWidget->show();




}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::getSetting()
{
    QSettings *configIniRead = NULL;
    QString path = QCoreApplication::applicationDirPath();
    path.append("/TcpServer.ini");
    configIniRead = new QSettings(path, QSettings::IniFormat);
    //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
    if(!configIniRead)
    {
        qDebug() <<"read ServerStatus.ini false";
        return false;
    }
    port = configIniRead->value("/SETTING/Port").toInt();
    //打印得到的结果
    qDebug() << "端口号 ="<<port;

    //读入入完成后删除指针
    delete configIniRead;
    return true;
}

void MainWindow::connectSer()
{
    //和服务器进行连接
    QString ip = "127.0.0.1";//获取ip地址
    if(!serverIP->setAddress(ip))//用这个函数判断IP地址是否可以被正确解析
    {
        //不能被正确解析就弹出一个警告窗口
        QMessageBox::warning(this, "错误", "IP地址不正确");
        return;
    }
    //创建一个通信套接字，用来和服务器进行通信
    tcpsocket = new QTcpSocket(this);

    //和服务器进行连接
    tcpsocket->connectToHost(*serverIP, port);

    //和服务器连接成功能会触发connected信号
    connect(tcpsocket, &QTcpSocket::connected, this, &MainWindow::slotconnectedsuccess);
    //接收到服务器的信息就会触发readyRead信号
    connect(tcpsocket, &QTcpSocket::readyRead, this, &MainWindow::slotreceive);

}

void MainWindow::slotconnectedsuccess()
{
    QJsonObject json;
    json.insert("Name", userName);
    json.insert("Type", "login");

    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    slotSendMsg(strJson);
}

void MainWindow::slotreceive()
{
    QByteArray bytes = tcpsocket->readAll();

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << QStringLiteral("解析Json失败");
        return;
    }

    // 解析Json
    QString userName,type,msg,color;
    int shape,size;
    QPoint lastPoint, endPoint;
    if (doucment.isObject())
    {
        QJsonObject obj = doucment.object();
        QJsonValue value;
        if (obj.contains("Name"))
        {
            value = obj.take("Name");
            if (value.isString())
            {
                userName = value.toString();
            }
        }
        if (obj.contains("Type"))
        {
            value = obj.take("Type");
            if (value.isString())
            {
                type = value.toString();
            }
        }
        if (obj.contains("msg"))
        {
            value = obj.take("msg");
            if (value.isString())
            {
                msg = value.toString();
            }
        }
        if (obj.contains("shape"))
        {
            value = obj.take("shape");
            if (value.isDouble())
            {
                shape = value.toInt();
            }
        }
        if (obj.contains("size"))
        {
            value = obj.take("size");
            if (value.isDouble())
            {
                size = value.toInt();
            }
        }
        if (obj.contains("color"))
        {
            value = obj.take("color");
            if (value.isString())
            {
                color = value.toString();
            }
        }

        if (obj.contains("lastPoint"))
        {

            QJsonObject o = obj.value("lastPoint").toObject();
            int x = o["x"].toInt();
            int y = o["y"].toInt();
            lastPoint.setX(x);
            lastPoint.setY(y);
        }

        if (obj.contains("endPoint"))
        {
            QJsonObject o = obj.value("endPoint").toObject();

            int x = o["x"].toInt();
            int y = o["y"].toInt();
            endPoint.setX(x);
            endPoint.setY(y);


        }
    }
    if(type == "chat")
    {
        QString info = userName;
        info.append(":\r\n");
        info.append("\t");
        info.append(msg);
        m_chatWidget->setMsg(info);
    }
    else if(type == "shape"){
        m_chatWidget->setshape(shape);

    }
    else if(type == "size"){
        m_chatWidget->setSize(size);

    }
    else if(type == "color"){

        m_chatWidget->setcolor(color);
    }
    else if(type == "paint"){

        m_chatWidget->Paint(shape,lastPoint,endPoint);
    }
    else if(type == "Clear"){

        m_chatWidget->setclear();
    }

}

void MainWindow::slotSendMsg(QString msg)
{
    tcpsocket->write(msg.toUtf8().data());

}

void MainWindow::slot_login(QString user)
{
    m_loginWidget->close();
    m_chatWidget = new ChatWidget();

    connect(m_chatWidget, &ChatWidget::sendMsg, this, &MainWindow::slotSendMsg);

    m_chatWidget->show();
    m_chatWidget->setUser(user);
}
