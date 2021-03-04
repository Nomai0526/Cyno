#include "settingswidget.h"

settingsWidget::settingsWidget(QWidget *parent) : QWidget(parent)
{

}
settingsWidget::settingsWidget(currentAccount *cAccount)
{
    this->resize(500,300);
    socketOfSettings = new QTcpSocket(this);
    socketOfSettings->connectToHost("192.168.33.141", 8000);    //连接服务器
    changeAvatar = new QPushButton(this);
    changeUserName = new QPushButton(this);
    changeSignature = new QPushButton(this);
    changePassword = new QPushButton(this);
    changeSessionBack = new QPushButton(this);
    newUserName= new QLineEdit(this);
    newSignature = new QLineEdit(this);
    newPassword = new QLineEdit(this);
    layout = new QGridLayout(this);
    changeAvatar->setText("更改头像");
    changeUserName->setText("更改昵称");
    changeSignature->setText("更改签名");
    changePassword->setText("更改密码");
    changeSessionBack->setText("更改聊天背景");
    layout->addWidget(changeAvatar,0,0,1,2);
    layout->addWidget(changeUserName,3,0,1,1);
    layout->addWidget(newUserName,3,1,1,1);
    layout->addWidget(changeSignature,4,0,1,1);
    layout->addWidget(newSignature,4,1,1,1);
    layout->addWidget(changePassword,5,0,1,1);
    layout->addWidget(newPassword,5,1,1,1);
    layout->addWidget(changeSessionBack,2,0,1,2);   //设置按钮与布局
    this->setLayout(layout);
    this->cAccount = cAccount;                      //将构造的形参转为成员变量以方便调用

    changeAvatar->setFixedHeight(30);
    changeUserName->setFixedHeight(30);
    changePassword->setFixedHeight(30);
    changeSessionBack->setFixedHeight(30);
    changeSignature->setFixedHeight(30);

    newUserName->setFixedHeight(30);
    newSignature->setFixedHeight(30);
    newPassword->setFixedHeight(30);

    changeAvatar->setStyleSheet("border:1px groove gray;border-radius:5px;padding:2px 4px;background-color: white");
    changeUserName->setStyleSheet("border:1px groove gray;border-radius:5px;padding:2px 4px;background-color: white");
    changePassword->setStyleSheet("border:1px groove gray;border-radius:5px;padding:2px 4px;background-color: white");
    changeSessionBack->setStyleSheet("border:1px groove gray;border-radius:5px;padding:2px 4px;background-color: white");
    changeSignature->setStyleSheet("border:1px groove gray;border-radius:5px;padding:2px 4px;background-color: white");

    changeAvatar->setFont(QFont("楷体",10,QFont::Bold));
    changeUserName->setFont(QFont("楷体",10,QFont::Bold));
    changePassword->setFont(QFont("楷体",10,QFont::Bold));
    changeSessionBack->setFont(QFont("楷体",10,QFont::Bold));
    changeSignature->setFont(QFont("楷体",10,QFont::Bold));

    connect(socketOfSettings, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(changeAvatar,SIGNAL(clicked(bool)),this,SLOT(changeAvatarSlot()));
    connect(changeUserName,SIGNAL(clicked(bool)),this,SLOT(changeUserNameSlot()));
    connect(changeSignature,SIGNAL(clicked(bool)),this,SLOT(changeSignatureSlot()));
    connect(changePassword,SIGNAL(clicked(bool)),this,SLOT(changePasswordSlot()));
    connect(changeSessionBack,SIGNAL(clicked(bool)),this,SLOT(changeSessionBackSlot()));
}

void settingsWidget::changeAvatarSlot() //改变头像的槽函数
{
    QString newAvatar = QFileDialog::getOpenFileName(this,"选择新头像" , "C:" ,"Image Files(*.jpg *.png)");                                            //这段之后在写
    if(newAvatar!="")
    socketOfSettings->write("changeUserInfo "+QString::number(cAccount->account).toUtf8()+" avatar "+newAvatar.toUtf8());
    //发送更改消息，消息格式为changeUseInfo account 更改项目 新项目
}

void settingsWidget::changeUserNameSlot()   //改变用户名的槽函数
{
    if(newUserName->text()!="")
    socketOfSettings->write("changeUserInfo "+QString::number(cAccount->account).toUtf8()+" username "+newUserName->text().toUtf8()); //发送更改昵称消息，格式同上
}

void settingsWidget::changeSignatureSlot()    //改变签名的槽函数
{
    if(newSignature->text()!="")
    socketOfSettings->write("changeUserInfo "+QString::number(cAccount->account).toUtf8()+" signature "+newSignature->text().toUtf8()); //发送更改签名消息，格式同上
}

void settingsWidget::changePasswordSlot()       //改变密码的槽函数
{
    if(newPassword->text()!="")
    socketOfSettings->write("changeUserInfo "+QString::number(cAccount->account).toUtf8()+" password "+newPassword->text().toUtf8()); //发送更改密码消息，格式同上
}

void settingsWidget::changeSessionBackSlot()      //改变对话窗口背景的槽函数
{
    QString newSessionBack = QFileDialog::getOpenFileName(this,"选择新对话背景" , "C:" ,"Image Files(*.jpg *.png)");
    if(newSessionBack!="")
    sessionWidgetBack = newSessionBack;
}
void settingsWidget::readData()
{
    QByteArray buffer;
    buffer = socketOfSettings->readAll();
    QString info = QByteArray(buffer);
    QStringList list;
    list = info.split(" ");
    if(list.at(0)=="changeUserInfo")
    {
        QDialog *changeSuccess= new QDialog(this);
        changeSuccess->resize(300,200);
        changeSuccess->setWindowTitle("修改成功！");
        changeSuccess->show();                      //收到修改成功的消息后显示对话窗口
    }
}
void settingsWidget::paintEvent(QPaintEvent *)
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
