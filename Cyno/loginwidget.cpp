#include "loginwidget.h"

loginWidget::loginWidget(QWidget *parent) : QWidget(parent)
{
    this->resize(640,360);
    accountLine = new QLineEdit(this);
    passwordLine = new QLineEdit(this);     //创建账号和密码框
    registerButton = new QPushButton(this);
    loginButton = new QPushButton(this);    //定义登陆和注册按钮
    loginFailure = new QDialog(this);
    registerButton->setText("注册");
    loginButton->setText("登录");
    loginFailure->setWindowTitle("登录失败！");      //定义注册弹框
    loginFailure->setFixedSize(300,200);
    layout= new QGridLayout(this);          //定义栅格布局
    layout->addWidget(accountLine,0,0,1,2);
    layout->addWidget(passwordLine,1,0,1,2);
    layout->addWidget(loginButton,3,0,1,1);
    layout->addWidget(registerButton,3,1,1,1);
    this->setLayout(layout);            //设置布局

    accountLine->setFixedHeight(50);
    passwordLine->setFixedHeight(50);
    accountLine->setPlaceholderText("账号");
    passwordLine->setPlaceholderText("密码");
    passwordLine->setEchoMode(QLineEdit::Password);
    accountLine->setAlignment(Qt::AlignCenter);
    passwordLine->setAlignment(Qt::AlignCenter);
    accountLine->setFont(QFont("Timers",70,QFont::Bold));
    passwordLine->setFont(QFont("Timers",70,QFont::Bold));      //美化以及人性化设置

    loginButton->setFixedHeight(50);
    registerButton->setFixedHeight(50);
    loginButton->setStyleSheet("border:4px groove gray;border-radius:10px;padding:2px 4px;background-color: white");
    registerButton->setStyleSheet("border:4px groove gray;border-radius:10px;padding:2px 4px;background-color: white");

    accountLine->setStyleSheet("border:1px olid rgb(41,57,85);border-radius: 3px;background: white;selection-background-color: green; ;font-size: 14px ;}");
    passwordLine->setStyleSheet("border:1px olid rgb(41,57,85);border-radius: 3px;background: white;selection-background-color: green; ;font-size: 14px ;}");

    QIntValidator * IntValidator = new QIntValidator;
    accountLine->setValidator(IntValidator);                    //限制账号仅为数字

    socketOfCyno = new QTcpSocket();
    socketOfCyno->connectToHost("192.168.33.141", 8000);

    connect(loginButton,SIGNAL(clicked()),this,SLOT(readAccountAndPassword()));     //将登陆连接入槽
    connect(registerButton,SIGNAL(clicked()),this,SLOT(registerPageAppear()));      //将注册连接入槽
    connect(socketOfCyno, SIGNAL(readyRead()), this, SLOT(ReadData()));
}
void loginWidget::readAccountAndPassword()//本函数用于读取并比较账号与密码
{
    QString registerInfo;
    registerInfo ="searchUserInfo "+accountLine->text();
    socketOfCyno->write(registerInfo.toUtf8());
}
void loginWidget::registerPageAppear()      //此函数用于打开注册页面
{
    registerWidget *registerPage =new registerWidget();
    registerPage->show();
}
void loginWidget::ReadData()
{
    if (numberOfLoginSuccess==1)
        return;                                 //这里由于是与主页面共用一个tcpClient，所以存在误读发给主页面的消息的情况，因此在登录成功一次后，即不再读取
    QByteArray buffer;
    buffer = socketOfCyno->readAll();
    QString info = QByteArray(buffer);
    QStringList list;
    list = info.split(" ");
    if (this->passwordLine->text()==list.at(1)&&this->accountLine->text()==list.at(0))      //如果帐号与密码都相同则登录成功
    {
        cAccount = new currentAccount(list);
        mainWidget *mainWidgetOfCyno = new mainWidget(cAccount);
        mainWidgetOfCyno->show();
        this->close();
        socketOfCyno->write(QString("online %1 true").arg(this->accountLine->text()).toUtf8());// 向服务器发送登陆成功确认信息
        numberOfLoginSuccess++;
    }
    else
        if(this->passwordLine->text()!=list.at(1)&&this->accountLine->text()==list.at(0))
        loginFailure->show();
}
void loginWidget::paintEvent(QPaintEvent* event)
{
    QPixmap  pixmap = QPixmap(":/new/prefix1/resources/defaultBack.jpg").scaled(this->size());
    //pixmap对象
    QPainter painter1(this);
    painter1.drawPixmap(this->rect(), pixmap);              //绘制登陆页面的背景
}
