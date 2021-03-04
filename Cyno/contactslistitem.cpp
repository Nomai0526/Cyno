#include "contactslistitem.h"

contactsListItem::contactsListItem(currentAccount *cAccount, QString avatar, QString account, QString username,QString online)
{
    this->cAccount = cAccount;
    this->account = account;
    this->username = username;
    accountLabel = new QLabel(this);
    usernameLabel = new QLabel(this);
    avatarLabel = new QLabel(this);
    onlineLabel = new QLabel(this);
    deleteContacts = new QPushButton(this);
    sendMessage = new QPushButton(this);
    layout = new QGridLayout(this);
    layout->addWidget(avatarLabel,0,0,3,3);
    layout->addWidget(accountLabel,1,3,1,3);
    layout->addWidget(usernameLabel,1,6,1,3);
    layout->addWidget(onlineLabel,1,9,1,3);
    layout->addWidget(sendMessage,1,12,1,2);
    layout->addWidget(deleteContacts,1,14,1,2);
    this->setLayout(layout);
    avatarLabel->setText(avatar);
    accountLabel->setText(account);
    usernameLabel->setText(username);
    deleteContacts->setText("删除好友");               //设置布局
    sendMessage->setText("发送消息");

    QImage *cAvatar = new QImage();
    cAvatar->load(":/new/prefix1/resources/sessionAvatarP.jpg");
    QPixmap pixmap = QPixmap::fromImage(*cAvatar);
    int width = avatarLabel->height();
    int height = avatarLabel->height();
    QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    avatarLabel->setPixmap(fitpixmap);                      //设置头像

    deleteContacts->setFixedHeight(30);
    deleteContacts->setStyleSheet("border:2px groove gray;border-radius:4px;padding:2px 4px;background-color: white");
    sendMessage->setFixedHeight(30);
    sendMessage->setStyleSheet("border:2px groove gray;border-radius:4px;padding:2px 4px;background-color: white");

    accountLabel->setFont(QFont("黑体",10,QFont::Bold));
    usernameLabel->setFont(QFont("黑体",10));
    onlineLabel->setFont(QFont("黑体",10));
    deleteContacts->setFont(QFont("楷体",10,QFont::Bold));
    sendMessage->setFont(QFont("楷体",10,QFont::Bold));

    if(online=="1")
        onlineLabel->setText("在线");
    else
        onlineLabel->setText("离线");                         //设置在线状态

    connect(deleteContacts,SIGNAL(clicked(bool)),this,SLOT(deleteContactsSlot()));
    connect(sendMessage,SIGNAL(clicked(bool)),this,SLOT(sendMessageSlot()));
}

void contactsListItem::deleteContactsSlot()
{
    if( QMessageBox::question(this,tr("删除好友"),tr("你确定要删除好友吗？"),QMessageBox::Yes, QMessageBox::No )== QMessageBox::Yes)
    {                               //再删除好友之前进行询问
        ContactsSocket = new QTcpSocket(this);
        ContactsSocket->connectToHost("192.168.33.141", 8000);
        QString info;
        info = "changeContacts "+QString::number(cAccount->account)+" "+account;    //发出删除好友的消息
        ContactsSocket->write(info.toUtf8());                 //删除好友的函数
        this->close();
    }
}
void contactsListItem::sendMessageSlot()
{
    receiver = new currentAccount();
    receiver->account = account.toInt();
    receiver->username = username;

    sessionWidget *anSessionWidget = new sessionWidget(cAccount,receiver);
    anSessionWidget->show();                //如果按下发送消息按钮，则创建会话窗口
}
