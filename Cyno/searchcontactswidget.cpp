#include "searchcontactswidget.h"

searchContactsWidget::searchContactsWidget(QWidget *parent) : QWidget(parent)
{

}
searchContactsWidget::searchContactsWidget(currentAccount *cAccount)
{
    this->cAccount = cAccount;
    this->setWindowTitle("CynoSearch");
    this->resize(700,400);
    search = new QPushButton(this);
    key = new QLineEdit(this);
    layout = new QGridLayout(this);
    resultsList = new QListWidget();
    layout->addWidget(key,0,0,1,3);
    layout->addWidget(search,0,3,1,1);
    layout->addWidget(resultsList,1,0,4,4);
    search->setText("搜索");
    this->setLayout(layout);            //布局设置

    key->setFixedHeight(30);
    search->setFixedHeight(30);
    search->setStyleSheet("border:4px groove gray;border-radius:10px;padding:2px 4px;background-color: white");

    search->setFont(QFont("楷体",10,QFont::Bold));

    connect(search,SIGNAL(clicked(bool)),this,SLOT(searchslot()));
}
void searchContactsWidget::searchslot()                 //按下搜索后执行的槽函数
{
    resultsList->clear();                                //这里要先清空之前的内容
    searchSocket = new QTcpSocket(this);
    searchSocket->connectToHost("192.168.33.141", 8000);
    searchSocket->write("searchNewContact "+key->text().toUtf8());
    connect(searchSocket,SIGNAL(readyRead()),this,SLOT(readData()));        //把槽放在这，否则无法读取信号
}
void searchContactsWidget::readData()
{
    QByteArray buffer;
    buffer = searchSocket->readAll();
    QString info = QByteArray(buffer);
    QStringList results;
    QStringList anContact;
    results = info.split("#");          //这里用#分割不同的结果
    for(int i=0;i<results.length()-1;i++)       //这里-1，是因为传过来的字符串末尾有一个#，会使分离出的结果多一个字符串
    {
        QString anResultString = results.at(i);
        anContact = anResultString.split(" ");
        QListWidgetItem *item = new QListWidgetItem(resultsList);
        searchResultItem *resultItem = new searchResultItem(QString::number(cAccount->account),anContact.at(1),anContact.at(0),anContact.at(2));
        resultsList->addItem(item);
        item->setSizeHint(QSize(0,70));
        resultsList->setItemWidget(item,resultItem);    //按照收到的信号创建窗口并设置窗口条目
    }
}
void searchContactsWidget::paintEvent(QPaintEvent *)
{
    if(mainWidgetBack=="")
    {
        QPixmap pixmap = QPixmap(":/new/prefix1/resources/defaultSessionBack3.jpg").scaled(this->size());
        QPainter painter(this);
        painter.drawPixmap(this->rect(), pixmap);
    }
    else
    {
     QPixmap pixmap = QPixmap(mainWidgetBack).scaled(this->size());
     QPainter painter(this);
     painter.drawPixmap(this->rect(), pixmap);
    }                                   //如果设置过主页面背景，则绘制该背景，否则绘制默认背景
}
