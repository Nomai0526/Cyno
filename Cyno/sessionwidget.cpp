#include "sessionwidget.h"
sessionWidget::sessionWidget(QWidget *parent) : QWidget(parent)
{

}

sessionWidget::sessionWidget(currentAccount *cAccount,currentAccount *receiver)                 //这个参数用来确定对话人
{
    cynoSql = new clientSqlAdmin(cAccount);
    socketOfSesssion = new QTcpSocket;
    socketOfSesssion->connectToHost("192.168.33.141", 8000);
    this->setWindowTitle(receiver->username);
    this->resize(600,800);
    this->cAccount = cAccount;
    this->receiver = receiver;                                                        //这里把形参化为实参，起过度作用
    messageList = new QListWidget(this);
    historyButton = new QPushButton(this);
    clearButton = new QPushButton(this);
    sendMessageButton = new QPushButton(this);
    messageToSend = new QTextEdit(this);
    Layout = new QGridLayout(this);
    historyButton->setText("历史记录");
    clearButton->setText("清空");
    sendMessageButton->setText("发送信息");
    sendMessageButton->setFixedHeight(40);
    Layout->addWidget(messageList,0,0,8,8);
    Layout->addWidget(historyButton,8,0,1,2);
    Layout->addWidget(clearButton,8,2,1,2);
    Layout->addWidget(messageToSend,9,0,2,6);
    Layout->addWidget(sendMessageButton,9,6,2,2);
    this->setLayout(Layout);                                        //对对话窗口的页面设置，布局仿照qq对话窗口
    messageList->setStyleSheet("background-color:transparent");
    messageList->setStyleSheet("background-color:transparent");

    QString temp;
    temp="searchUserInfo "+QString::number(cAccount->account);
    socketOfSesssion->write(temp.toUtf8());                         //发送查询消息

    historyButton->setStyleSheet("border:1px groove gray;border-radius:10px;padding:2px 4px;background-color: white");
    clearButton->setStyleSheet("border:1px groove gray;border-radius:10px;padding:2px 4px;background-color: white");
    sendMessageButton->setStyleSheet("border:1px groove gray;border-radius:10px;padding:2px 4px;background-color: white");

    historyButton->setFont(QFont("楷体",10,QFont::Bold));
    clearButton->setFont(QFont("楷体",10,QFont::Bold));
    sendMessageButton->setFont(QFont("楷体",10,QFont::Bold));
    messageToSend->setFont(QFont("黑体",10));

    connect(clearButton,SIGNAL(clicked(bool)),messageList,SLOT(clear()));
    connect(sendMessageButton,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(socketOfSesssion, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(historyButton,SIGNAL(clicked(bool)),this,SLOT(showHistory()));
}

void sessionWidget::sendMessage()
{
    QTime *time = new QTime();
    QString strTime;
    strTime = time->currentTime().toString("hh:mm:ss");
    QDate *date = new QDate();
    QString strDate;
    strDate = date->currentDate().toString("dd.MM.yyyy");           //获得现在的日期和时间
    QString message = "messageTransport " + QString::number(receiver->account) + " " +
            QString::number(cAccount->account)+ " " + messageToSend->toPlainText()+" "+strDate+" "+strTime+" "+cAccount->username;
    //发送的信息格式为 messageTransport receiver sender messsage date time
    messageToSend->clear();
    QStringList tempList = message.split(" ");
    if(tempList.at(3) == "")
        return;         //如果带发送消息为空，则结束

    sessionListItem *anSessionListItem = new sessionListItem(this->cAccount,tempList.at(3),strDate,strTime);
    QListWidgetItem *item = new QListWidgetItem(messageList);
    messageList->addItem(item);
    item->setSizeHint(QSize(0,90));
    messageList->setItemWidget(item,anSessionListItem);   //建立一个特定的窗口对象，并将其设为一项
    socketOfSesssion->write(message.toUtf8());              //根据目前的内容以及时间构建消息
    QString messageToSql = receiver->username +" "+cAccount->username+" "+tempList.at(3)+" "+strDate+" "+strTime;
    cynoSql->addMessage(messageToSql);                                      //向数据库中添加记录
}
void sessionWidget::ReadData()
{
    QByteArray buffer;
    buffer = socketOfSesssion->readAll();
    QString info = QByteArray(buffer);
    QStringList list;
    list = info.split(" ");
    if(list.at(0)=="messageTransport"&&list.at(2)==QString::number(receiver->account))  //如果消息头符合条件且接收人符合条件才会展示消息
    {
        sessionListItem *anSessionListItem = new sessionListItem(this->receiver,list.at(3),list.at(4),list.at(5));
        QListWidgetItem *item = new QListWidgetItem(messageList);
        messageList->insertItem(0,item);
        item->setSizeHint(QSize(0,90));
        messageList->setItemWidget(item,anSessionListItem);   //建立一个特定的窗口对象，并将其设为一项
        QString messageToSql = cAccount->username +" "+receiver->username+" "+messageToSend->toPlainText()+" "+list.at(4)+" "+list.at(5);
        cynoSql->addMessage(messageToSql);
    }
}

void sessionWidget::showHistory()   //按下历史按钮会新建一个历史窗口
{
    historyWidget *history = new historyWidget(cAccount,receiver);
    history->show();
}
void sessionWidget::paintEvent(QPaintEvent *)
{
    if(sessionWidgetBack=="")
    {
        QPixmap pixmap = QPixmap(":/new/prefix1/resources/defaultSessionBack3.jpg").scaled(this->size());
        QPainter painter(this);
        painter.drawPixmap(this->rect(), pixmap);
    }
    else
    {
     QPixmap pixmap = QPixmap(sessionWidgetBack).scaled(this->size());
     QPainter painter(this);
     painter.drawPixmap(this->rect(), pixmap);
    }                                   //如果设置过对话页面背景，则绘制该背景，否则绘制默认背景
}
