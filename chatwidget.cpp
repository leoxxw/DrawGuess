#include "chatwidget.h"
#include "ui_chatwidget.h"
#include <QColorDialog>
#include <QJsonObject>
#include <QJsonDocument>


ChatWidget::ChatWidget(BaseMainWidget *parent) :
    BaseMainWidget(parent),
    ui(new Ui::ChatWidget),
    area(NULL),
    nType(0)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    initListWidget();
    ui->lineEdit->setValidator(new QIntValidator(0, 100, this)); //0, 20为输入的数字值范围
    area=ui->widget_11;
    area->hide();
    connect(area, &paintWidget::signal_paint, this, &ChatWidget::slot_paint);


    initCombox();
    ui->lineEdit->setText("2");

}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::initListWidget()
{
    ui->listWidget->setIconSize(QSize(50,30));
    ui->listWidget->setFocusPolicy(Qt::NoFocus);

    //    QListWidgetItem *add_item = new QListWidgetItem(ui->listWidget);
    //    add_item->setIcon(QIcon(":/res/pix/add.png"));
    //    add_item->setText(tr("Add"));
    //    //设置item项中的文字位置
    //    add_item->setTextAlignment(Qt::AlignHCenter);
    //    add_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    //设置viewModel，来确定使用不同的视图进行显示
    //使ListWidgetItem中的图标在上，文字在下
    //ui->listWidget->setViewMode(QListView::IconMode);
    //ui->listWidget->setViewMode(QListWidget::IconMode);  //这样的形式也可以
    //ui->listWidget->setViewMode(QListView::ListMode);


    //改变item大小，使用QListWidgetItem::setSizeHint()
    //add_item->setSizeHint(QSize(60,60));


    //设置ListWidget可以选择多个item
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);


    //有两种方法在ListWidget中添加item
    //    //一种在构造item的时候，指定其父Widget
    //    QListWidgetItem *cubby_item = new QListWidgetItem(QIcon(":/image/PNG/face.png"),
    //                                                      tr("leo"),ui->listWidget);

    //    ui->listWidget->addItem(cubby_item);
    //    //第二种方法是在构造完item后，使用QListWidget::additem()来添加item
    //    QListWidgetItem *dropbox_item = new QListWidgetItem();
    //    dropbox_item->setIcon(QIcon(":/image/PNG/face.png"));
    //    dropbox_item->setText(tr("sherry"));
    //    ui->listWidget->addItem(dropbox_item);


    //    //向QListWidget中指定的位置插入itemm，使用QListWidget::addItem()
    //    QListWidgetItem *google_item = new QListWidgetItem(QIcon(":/image/PNG/face.png"),
    //                                                         tr("Google"));
    //    ui->listWidget->insertItem(1,google_item);


    //使用QListWidget::takeItem(int index)来删除表中的某一项
    //ui->listWidget->takeItem(0);

    //删除item，必须要加上delete item，否则删不掉
    //ui->listWidget->removeItemWidget(add_item);
    //delete add_item;


    //打开和关闭item是否可以编辑,默认不可编辑
    //使用QListWidget::openPersistenEditor(QListWidgetItem*)和
    //QListWidget::closePersistentEditor(QListWidgetItem*)
    //ui->listWidget->openPersistentEditor(cubby_item);


    //设置当前的item是第几行
    //初始化ListWidget显示时，指向哪一行
    ui->listWidget->setCurrentRow(1);


    //设置ListWidget是否可以自动排序,默认是false
    //ui->listWidget->setSortingEnabled(true);


    //设置QLisView大小改变时，图标的调整模式，默认是固定的，可以改成自动调整
    //ui->listWidget->setResizeMode(QListView::Adjust);
    //设置列表可以拖动，如果想固定不能拖动，使用QListView::Static
    //拖动item，进行复制
    ui->listWidget->setMovement(QListWidget::Free);


    QListWidgetItem *leo_item = new QListWidgetItem();
    QString strleo(tr("leo"));
    leo_item->setData(Qt::DisplayRole,strleo);
    leo_item->setIcon(QIcon(":/image/PNG/face.png"));
    ui->listWidget->addItem(leo_item);

    QListWidgetItem *sherry_item = new QListWidgetItem();
    QString strsherry(tr("cherry"));
    sherry_item->setData(Qt::DisplayRole,strsherry);
    sherry_item->setIcon(QIcon(":/image/PNG/face.png"));
    ui->listWidget->addItem(sherry_item);


    //    QPushButton *button = new QPushButton(tr("Button"));
    //    QListWidgetItem *button_item = new QListWidgetItem();
    //    ui->listWidget->addItem(button_item);
    //    //实现替换，自定义item
    //    ui->listWidget->setItemWidget(button_item,button);

    //    //使用QListWidget::count()来统计ListWidget中总共的item数目
    //    int item_count = ui->listWidget->count();
    // qDebug()<<item_count;

}

void ChatWidget::setMsg(QString msg)
{
    ui->textBrowser->append(msg);
}

void ChatWidget::initCombox()
{
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(boxChange(int)));
    itemDelegate = new QStyledItemDelegate();
    ui->comboBox->setItemDelegate(itemDelegate);
    ui->comboBox->addItem(QStringLiteral("直线"));
    ui->comboBox->addItem(QStringLiteral("矩形"));
    ui->comboBox->addItem(QStringLiteral("圆形"));
    ui->comboBox->addItem(QStringLiteral("画刷"));
    ui->comboBox->addItem(QStringLiteral("橡皮擦"));
}


void ChatWidget::on_pushButton_min_clicked()
{
    this->showMinimized();
}

void ChatWidget::on_pushButton_max_clicked()
{
    if(this->isFullScreen())
    {
        this->showNormal();
        ui->pushButton_max->setIcon(QIcon(":/image/PNG/Zuidahua.down.png"));

    }
    else
    {
        this->showFullScreen();

        ui->pushButton_max->setIcon(QIcon(":/image/PNG/Zuidahua_t.down.png"));
    }
}

void ChatWidget::on_pushButton_close_clicked()
{
    this->close();
}

void ChatWidget::on_pushButton_clo_clicked()
{

}

void ChatWidget::on_pushButton_send_clicked()
{
    QString msg = ui->textEdit->toPlainText();

    QJsonObject json;
    json.insert("Name", user);
    json.insert("Type", "chat");
    json.insert("msg", msg);

    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    emit sendMsg(strJson);

    QString info = user;
    info.append(":\r\n");
    info.append("\t");
    info.append(msg);

    ui->textBrowser->append(info);
    ui->textEdit->clear();
}

void ChatWidget::on_pushButton_chat_clicked()
{
    nType = 0;
    area->hide();

    QString info = ("QPushButton#pushButton_paint{ \
            background-color: rgb(235, 242, 249);\
            border: 0px solid grey;  \
            border-radius:0px; \
            font: 75 10pt '微软雅黑';\
            color:grey;\
            }");
    ui->pushButton_paint->setStyleSheet(info);

     info = ("QPushButton#pushButton_chat{ \
            background-color: rgb(227, 227, 229);\
            border: 0px solid grey;  \
            border-radius:0px; \
            font: 75 10pt '微软雅黑';\
            color:grey;\
            }");

    ui->pushButton_chat->setStyleSheet(info);
}

void ChatWidget::on_pushButton_paint_clicked()
{
    QString info = ("QPushButton#pushButton_chat{ \
            background-color: rgb(235, 242, 249);\
            border: 0px solid grey;  \
            border-radius:0px; \
            font: 75 10pt '微软雅黑';\
            color:grey;\
            }");

    ui->pushButton_chat->setStyleSheet(info);

     info = ("QPushButton#pushButton_paint{ \
            background-color: rgb(227, 227, 229);\
            border: 0px solid grey;  \
            border-radius:0px; \
            font: 75 10pt '微软雅黑';\
            color:grey;\
            }");
    ui->pushButton_paint->setStyleSheet(info);

    nType = 1;
    area->show();
    area->setbPaint(true);
}

void ChatWidget::boxChange(int index)
{
    shape t = (shape)index;
    area->setCurrentShape(t);

    QJsonObject json;
    json.insert("Name", user);
    json.insert("Type", "shape");
    json.insert("shape", index);

    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    emit sendMsg(strJson);
}

void ChatWidget::on_lineEdit_textChanged(const QString &arg1)
{
    int size = arg1.toInt();
    area->setPenSize(size);

    QJsonObject json;
    json.insert("Name", user);
    json.insert("Type", "size");
    json.insert("size", size);

    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    emit sendMsg(strJson);
}

void ChatWidget::on_pushButton_clicked()
{
    QColorDialog color;//调出颜色选择器对话框
    QColor c = color.getRgba();
    area->setPenColor(c);
    QString info = "QPushButton#pushButton{background-color:";
    QString strRgb =makeColorString(c,"RGB");
    info.append(strRgb);
    info.append(";");
    info.append("border: 1px solid grey; \
                border-radius:5px; \
            font: 75 10pt '微软雅黑';\
            color:grey;}");
    ui->pushButton->setStyleSheet(info);

    QJsonObject json;
    json.insert("Name", user);
    json.insert("Type", "color");
    json.insert("color", info);

    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    emit sendMsg(strJson);
}
QString ChatWidget::makeColorString(const QColor &color, const QString type)
{
    if(type == "RGBA") {
        return QString("rgba(%1, %2, %3, %4)")
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue())
                .arg(color.alpha());
    }
    if(type == "RGB") {
        return QString("rgba(%1, %2, %3)")
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue());
    }
    if(type == "HEX") {
        return QString().sprintf("#%1%02X%02X%02X",
                                 color.red(),
                                 color.green(),
                                 color.blue()).arg(color.alpha() != 255 ? QString().sprintf("%02X", color.alpha()) : QString());
    }

    return color.name();
}

void ChatWidget::setUser(QString user)
{
    this->user = user;
}

void ChatWidget::setshape(int index)
{
    ui->comboBox->setCurrentIndex(index);
    shape t = (shape)index;
    area->setCurrentShape(t);
}

void ChatWidget::setSize(int size)
{
    QString str= QString::number(size, 10);

    ui->lineEdit->setText(str);
    area->setPenSize(size);
}

void ChatWidget::setcolor(QString info)
{

    ui->pushButton->setStyleSheet(info);
    QPalette pal = ui->pushButton->palette();
    QBrush brush = pal.background();
    QColor c = brush.color();
    area->setPenColor(c);
}

void ChatWidget::setclear()
{
    area->setClear();
}

void ChatWidget::Paint(int type, QPoint lastPoint, QPoint endPoint)
{
    area->paintEx(type, lastPoint,  endPoint);
}

void ChatWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Return://数字键盘的Enter键
    case Qt::Key_Enter://Enter键
        on_pushButton_send_clicked();
        break;
    default:
        break;
    }
}

void ChatWidget::on_pushButton_2_clicked()
{
    area->setClear();
    QJsonObject json;
    json.insert("Name", user);
    json.insert("Type", "Clear");

    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    emit sendMsg(strJson);
}

void ChatWidget::slot_paint(shape type, QPoint lastPoint, QPoint endPoint)
{
    QJsonObject json;
    json.insert("Name", user);
    json.insert("Type", "paint");
    json.insert("shape", type);
    QJsonObject addLastPoint;
    addLastPoint.insert("x", lastPoint.x());
    addLastPoint.insert("y", lastPoint.y());
    json.insert("lastPoint", addLastPoint);

    QJsonObject addEndPoint;
    addEndPoint.insert("x", endPoint.x());
    addEndPoint.insert("y", endPoint.y());
    json.insert("endPoint", addEndPoint);

    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    emit sendMsg(strJson);
}
