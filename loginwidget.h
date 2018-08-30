#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "basemainwidget.h"
namespace Ui {
class loginwidget;
}

class loginwidget : public BaseMainWidget
{
    Q_OBJECT

public:
    explicit loginwidget(BaseMainWidget *parent = 0);
    ~loginwidget();
private:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_min_clicked();

    void on_pushButton_clo_clicked();
signals:
    void signals_login(QString user);

private:
    Ui::loginwidget *ui;
};

#endif // LOGINWIDGET_H
