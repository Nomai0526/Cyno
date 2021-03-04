#include "searchresultitem.h"

searchResultItem::searchResultItem(QString cAccount,QString avatar,QString account,QString username)
{
    this->cAccount = cAccount;
    this->account = account;
    accountLabel = new QLabel(this);
    usernameLabel = new QLabel(this);
    avatarLabel = new QLabel(this);
    addContacts = new QPushButton(this);
    layout = new QGridLayout(this);
    layout->addWidget(avatarLabel,0,0,3,3);
    layout->addWidget(accountLabel,1,3,1,3);
    layout->addWidget(usernameLabel,1,6,1,3);
    layout->addWidget(addContacts,1,9,1,2);
    this->setLayout(layout);
    avatarLabel->setText(avatar);
    accountLabel->setText(account);
    usernameLabel->setText(username);
    addContacts->setText("添加好友");

    QImage *cAvatar = new QImage();
    cAvatar->load(":/new/prefix1/resources/sessionAvatar.jpg");
    QPixmap pixmap = QPixmap::fromImage(*cAvatar);
    int width = avatarLabel->height();
    int height = avatarLabel->height();
    QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    avatarLabel->setPixmap(fitpixmap);

    accountLabel->setFont(QFont("黑体",10,QFont::Bold));
    usernameLabel->setFont(QFont("黑体",10));
    addContacts->setFont(QFont("楷体",10,QFont::Bold));

    addContacts->setFixedHeight(30);
    addContacts->setStyleSheet("border:2px groove gray;border-radius:4px;padding:2px 4px;background-color: white");

    connect(addContacts,SIGNAL(clicked(bool)),this,SLOT(addContactsSlot()));
}

void searchResultItem::addContactsSlot()
{
    addContactsSocket = new QTcpSocket(this);
    addContactsSocket->connectToHost("192.168.33.141", 8000);
    QString info;
    info = "addContacts "+cAccount+" "+account;
    addContactsSocket->write(info.toUtf8());
}
