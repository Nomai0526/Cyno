#include "cynoclient.h"

CynoClient::CynoClient(QWidget *parent) : QWidget(parent)
{
    //初始化TCP客户端
    edtIP = new QLineEdit(this);
    edtPort= new QLineEdit(this);
    connectButton= new QPushButton("连接",this);
    sendButton= new QPushButton("发送",this);
    textReceive= new QTextEdit(this);
    textSend=new QTextEdit(this);
    tcpServer= new QTcpServer(this);
    currentClient= new QTcpSocket(this);
    cbxConnection = new QComboBox(this); //创建各种部件
    layout =new QGridLayout(this);
    layout->addWidget(textReceive,0,0,4,4);
    layout->addWidget(edtIP,0,4,1,4);
    layout->addWidget(edtPort,1,4,1,4);
    layout->addWidget(connectButton,2,4,1,4);
    layout->addWidget(cbxConnection,3,4,1,4);
    layout->addWidget(textSend,4,0,2,6);
    layout->addWidget(sendButton,4,6,2,2);
    this->setLayout(layout);

    tcpClient = new QTcpSocket(this);   //实例化tcpClient
    tcpClient->abort();                 //取消原有连接
    connectButton->setEnabled(true);
    sendButton->setEnabled(false);

    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), \
            this, SLOT(ReadError(QAbstractSocket::SocketError)));
    connect(connectButton,SIGNAL(clicked(bool)),this,SLOT(on_btnConnect_clicked()));
    connect(sendButton,SIGNAL(clicked(bool)),this,SLOT(on_btnSend_clicked()));
}

void CynoClient::ReadData()
{
    QByteArray buffer = tcpClient->readAll();
    if(!buffer.isEmpty())
    {
        textReceive->append(buffer);
    }
}

void CynoClient::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    connectButton->setText(tr("连接"));
    QMessageBox msgBox;
    msgBox.setText(tr("failed to connect server because %1").arg(tcpClient->errorString()));
    msgBox.exec();
}

void CynoClient::on_btnConnect_clicked()
{
    if(connectButton->text()=="连接")
    {
        tcpClient->connectToHost(edtIP->text(), edtPort->text().toInt());
        if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
        {
            connectButton->setText("断开");
            sendButton->setEnabled(true);
        }
    }
    else
    {
        tcpClient->disconnectFromHost();
        if (tcpClient->state() == QAbstractSocket::UnconnectedState \
                || tcpClient->waitForDisconnected(1000))  //已断开连接则进入if{}
        {
            connectButton->setText("连接");
            sendButton->setEnabled(false);
        }
    }
}

void CynoClient::on_btnSend_clicked()
{
    QString data = textSend->toPlainText();
    if(data != "")
    {
        tcpClient->write(data.toLatin1()); //qt5出去了.toAscii()
    }
}

void CynoClient::on_pushButton_clicked()
{
    textReceive->clear();
}

