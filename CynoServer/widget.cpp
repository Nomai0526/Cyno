#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    accountToIP = new QStringList();
    sqladmin =new sqlAdmin();
    edtIP = new QLineEdit(this);
    edtPort= new QLineEdit(this);
    connectButton= new QPushButton("监听",this);
    textReceive= new QTextEdit(this);
    tcpServer= new QTcpServer(this);
    currentClient= new QTcpSocket(this);
    layout =new QGridLayout(this);
    layout->addWidget(textReceive,0,0,12,4);
    layout->addWidget(edtIP,0,4,1,4);
    layout->addWidget(edtPort,1,4,1,4);
    layout->addWidget(connectButton,2,4,1,4);
    this->setLayout(layout);
    tcpServer = new QTcpServer(this);
    edtIP->setText(QNetworkInterface().allAddresses().at(1).toString());   //获取本地IP
    connectButton->setEnabled(true);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));
    connect(tcpServer,SIGNAL(disconnect()),this,SLOT(disconnectedSlot()));
    connect(connectButton,SIGNAL(clicked(bool)),this,SLOT(on_btnConnect_clicked()));
}
void Widget::NewConnectionSlot()
{
    currentClient = tcpServer->nextPendingConnection();
    tcpClient.append(currentClient);

    connect(currentClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}

// 客户端数据可读信号，对应的读数据槽函数
void Widget::ReadData()
{
    QString message;
    // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
    for(int i=0; i<tcpClient.length(); i++)
    {
        QByteArray buffer = tcpClient[i]->readAll();    //如果读取的信息为空则忽略
        if(buffer.isEmpty())    continue;

        static QString IP_Port, IP_Port_Pre;
        IP_Port = QString("%1 %2").arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                .arg(tcpClient[i]->peerPort());
        message = QByteArray(buffer);
        infoList = message.split(" ");          //将收到的消息进行分割以便于处理，分割关键词为空格
        QString str = infoList.at(0);                       //识别信息头从而确定信息的种类
        if(str==QString::fromStdString("addUserInfo"))
        {
            sqladmin->addUserInfo(sqladmin->CynoServerSql,infoList); //收到注册指令时执行注册函数
        }
        if(str==QString::fromStdString("searchUserInfo"))    //收到登录指令时执行登录函数，登录函数返回密码
        {
            IP_Port = QString("%1 %2").arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                    .arg(tcpClient[i]->peerPort());
            accountToIP->append(infoList.at(1)+" "+IP_Port);
            numberOfConnectedClient++;
            if(numberOfConnectedClient==100)
                numberOfConnectedClient=0;
            QString info= sqladmin->searchUserInfo(sqladmin->CynoServerSql,infoList);
            currentClient->write(info.toUtf8());
        }
        if(str==QString::fromStdString("online"))
            sqladmin->setOnlineState(sqladmin->CynoServerSql,infoList);
        if(str==QString::fromStdString("searchNewContact"))
        {
            QString info= sqladmin->searchNewContact(sqladmin->CynoServerSql,infoList); //收到登录指令时执行登录函数，登录函数返回密码
            currentClient->write(info.toUtf8());
        }
        if(str==QString::fromStdString("changeUserInfo"))       //收到更改信息指令时执行该函数，更改数据库内容
        {
            sqladmin->changeUserInfo(sqladmin->CynoServerSql,infoList);
            currentClient->write("changeUserInfo success");
        }

        if(str==QString::fromStdString("addContacts"))          //收到添加好友信息执行该函数，更改数据库内容
            sqladmin->addContacts(sqladmin->CynoServerSql,infoList);

        if(str==QString::fromStdString("showContacts"))         //收到查询联系人信息时执行该函数，返回联系人列表
        {
            QString info= sqladmin->showContacts(sqladmin->CynoServerSql,infoList);
            currentClient->write(info.toUtf8());
        }
        if(str==QString::fromStdString("changeContacts"))       //收到改变联系人信息时执行该函数，更改数据库
            sqladmin->changeContacts(sqladmin->CynoServerSql,infoList);
        if(str==QString::fromStdString("messageTransport"))     //收到信息转发信息时执行该函数，直接进行数据转发
        {
            QStringList IP,Port;
            for(int i=0;i<numberOfConnectedClient;i++)
            {
                QStringList temp = accountToIP->at(i).split(" ");
                if (infoList.at(1)==temp.at(0))
                {
                    IP.append(temp.at(1));
                    Port.append(temp.at(2));
                }
            }
            for(int i=0;i<tcpClient.length();i++)
            {
                for(int k=0;k<IP.length();k++)
                {
                    if(IP.at(k)==tcpClient[i]->peerAddress().toString().split("::ffff:")[1]&&Port.at(k)==QString::number(tcpClient[i]->peerPort()))
                    {
                        tcpClient[i]->write(message.toUtf8());
                    }
                }
            }
        }
        if(IP_Port != IP_Port_Pre)              // 若此次消息的地址与上次不同，则需显示此次消息的客户端地址
            textReceive->append(IP_Port);

        textReceive->append(buffer);


        IP_Port_Pre = IP_Port;      //更新ip_port
    }
}
// disconnected -> disconnectedSlot 客户端断开连接的槽函数
void Widget::disconnectedSlot()
{
    //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            tcpClient[i]->destroyed();
            tcpClient.removeAt(i);
        }
    }
}
// 监听--断开
void Widget::on_btnConnect_clicked()
{
    if(connectButton->text()=="监听")
    {
        bool ok = tcpServer->listen(QHostAddress::Any, edtPort->text().toInt());
        if(ok)
        {
            connectButton->setText("断开");
        }
    }
    else
    {
        for(int i=0; i<tcpClient.length(); i++)//断开所有连接
        {
            tcpClient[i]->disconnectFromHost();
            bool ok = tcpClient[i]->waitForDisconnected(1000);
            if(!ok)
            {
                // 处理异常
            }
            tcpClient.removeAt(i);  //从保存的客户端列表中取去除
        }
        tcpServer->close();     //不再监听端口
        connectButton->setText("监听");
    }
}
Widget::~Widget()
{

}
