#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "basemainwidget.h"
#include "paintwidget.h"

#include <QStyledItemDelegate>
namespace Ui {
class ChatWidget;
}

class ChatWidget : public BaseMainWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(BaseMainWidget *parent = 0);
    ~ChatWidget();
    void initListWidget();
    void setMsg(QString msg);
    void initCombox();
    QString makeColorString(const QColor &color, const QString type);
    void setUser(QString user);

    void setshape(int index);

    void setSize(int size);

    void setcolor(QString info);

    void setclear();

    void Paint(int type, QPoint lastPoint, QPoint endPoint);

private:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_min_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_clo_clicked();

    void on_pushButton_send_clicked();
    void on_pushButton_chat_clicked();

    void on_pushButton_paint_clicked();

    void boxChange(int index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void slot_paint(shape type, QPoint lastPoint,QPoint endPoint);

signals:
    void sendMsg(QString msg);

private:
    Ui::ChatWidget *ui;
    paintWidget *area;//创建一个画图组件
    int nType;//0代表聊天，1 代表画图
    QStyledItemDelegate* itemDelegate;
    QString user;
};

#endif // CHATWIDGET_H
