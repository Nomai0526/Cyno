#include "registerwidget.h"

registerWidget::registerWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Cyno注册");
    this->resize(400,240);    //设置初始大小400*240
    accountLine = new QLineEdit(this);
    passwordLine = new QLineEdit(this);
    registerButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    loginFailure = new QDialog(this);
    loginSuccess = new QDialog(this);
    layout= new QGridLayout(this);          //定义栅格布局
    registerButton->setText("注册");
    cancelButton->setText("取消");         //定义登陆和注册按钮
    loginFailure->setWindowTitle("注册失败！");
    loginFailure->setWindowTitle("注册成功！");  //定义注册弹框
    layout->addWidget(accountLine,0,0,1,2);
    layout->addWidget(passwordLine,1,0,1,2);
    layout->addWidget(cancelButton,3,1,1,1);
    layout->addWidget(registerButton,3,0,1,1);
    this->setLayout(layout);            //设置布局
    loginFailure->setFixedSize(300,200);

    accountLine->setFixedHeight(20);
    passwordLine->setFixedHeight(20);
    accountLine->setPlaceholderText("账号(仅限数字)");
    passwordLine->setPlaceholderText("密码");
    passwordLine->setEchoMode(QLineEdit::Password);
    accountLine->setAlignment(Qt::AlignCenter);
    passwordLine->setAlignment(Qt::AlignCenter);
    accountLine->setFont(QFont("Timers",20,QFont::Bold));
    passwordLine->setFont(QFont("Timers",20,QFont::Bold));      //美化以及人性化设置

    cancelButton->setFixedHeight(40);
    registerButton->setFixedHeight(40);
    cancelButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: white");
    registerButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color: white");

    accountLine->setStyleSheet("border:1px olid rgb(41,57,85);border-radius: 3px;background: white;selection-background-color: green; ;font-size: 14px ;}");
    passwordLine->setStyleSheet("border:1px olid rgb(41,57,85);border-radius: 3px;background: white;selection-background-color: green; ;font-size: 14px ;}");

    QIntValidator * IntValidator = new QIntValidator;
    accountLine->setValidator(IntValidator);                    //限制账号仅为数字

    connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(close()));             //将取消按钮连接入槽
    connect(registerButton,SIGNAL(clicked(bool)),this,SLOT(registerslot()));
}
void registerWidget::registerslot()     //本函数用于注册
{
    QString registerInfo;
    registerInfo ="addUserInfo "+accountLine->text() + " " +passwordLine->text() + " ";
    QTcpSocket *tcpClient = new QTcpSocket(this);
    tcpClient->abort();
    tcpClient->connectToHost("192.168.33.141", 8000);
    if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
    {
         tcpClient->write(registerInfo.toUtf8());   //发送注册消息
    }
}
void registerWidget::paintEvent(QPaintEvent* event)
{
    QPixmap  pixmap = QPixmap(":/new/prefix1/resources/defaultBack.jpg").scaled(this->size());
    //pixmap对象
    QPainter painter1(this);
    painter1.drawPixmap(this->rect(), pixmap);              //绘制页面的背景
}
