
#include "contactswidget.h"

contactsWidget::contactsWidget(QWidget *parent): QWidget(parent)
{

}

contactsWidget::contactsWidget(currentAccount *cAccount)
{
    this->cAccount = cAccount;
    this->setWindowTitle("CynoContacts");
    this->resize(700,400);
    search = new QPushButton(this);
    key = new QLineEdit(this);
    layout = new QGridLayout(this);
    contactsList = new QListWidget();
    layout->addWidget(key,0,0,1,3);
    layout->addWidget(search,0,3,1,1);
    layout->addWidget(contactsList,1,0,4,4);
    search->setText("搜索");
    this->setLayout(layout);            //布局设置

    contactsSocket = new QTcpSocket(this);
    contactsSocket->connectToHost("192.168.33.141", 8000);
    QString info;
    info = "showContacts "+QString::number(cAccount->account);
    contactsSocket->write(info.toUtf8());       //连接服务器并发送查询消息

    key->setFixedHeight(30);
    search->setFixedHeight(30);
    search->setStyleSheet("border:4px groove gray;border-radius:10px;padding:2px 4px;background-color: white");

    search->setFont(QFont("楷体",10,QFont::Bold));

    connect(contactsSocket,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(search,SIGNAL(clicked(bool)),this,SLOT(searchSlot()));
}

void contactsWidget::readData()
{
    QByteArray buffer;
    buffer = contactsSocket->readAll();
    QString info = QByteArray(buffer);
    QStringList results;
    QStringList anContact;
    contactsNumber = new QStringList();
    results = info.split("#");          //这里用#分割不同的结果
    for(int i=0;i<results.length()-1;i++) //这里-1，是因为传过来的字符串末尾有一个#，会使分离出的结果多一个字符串
    {
        QString anResultString = results.at(i);
        anContact = anResultString.split(" ");
        contactsNumber->append(anContact.at(0)+" "+anContact.at(2));
        QListWidgetItem *item = new QListWidgetItem(contactsList);
        contactsListItem *anContactsListItem = new contactsListItem(cAccount,anContact.at(1),anContact.at(0),anContact.at(2),anContact.at(4));
        contactsList->addItem(item);
        item->setSizeHint(QSize(0,70));
        contactsList->setItemWidget(item,anContactsListItem);   //建立一个特定的窗口对象，并将其设为一项
    }
}

void contactsWidget::searchSlot()               //搜索项的函数
{
    for(int i=0;i<contactsNumber->length();i++)
    {
        contactsList->item(i)->setHidden(false);            //首先将所有项设置显示
        QString tempString = contactsNumber->at(i);
        QStringList tempStringList = tempString.split(" ");
        if(key->text()!=tempStringList.at(0)&&key->text()!=tempStringList.at(1))        //判断某个项的账号或者昵称是否与搜索框内容相同
        {
            contactsList->item(i)->setHidden(true);         //如果都不同则隐藏
        }
        if(key->text()=="")
            contactsList->item(i)->setHidden(false);        //如果搜索框为空则显示所有好友
    }
}
void contactsWidget::paintEvent(QPaintEvent *)
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
