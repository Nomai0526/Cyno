#include "sessionlistitem.h"

sessionListItem::sessionListItem(QWidget *parent) : QWidget(parent)
{

}
sessionListItem::sessionListItem(currentAccount *Account, QString message,QString date,QString time)
{

    this->setFixedSize(560,100);
    avatarLabel = new QLabel(this);
    nameLabel = new QLabel(this);
    contentsLabel = new QLabel(this);
    timeLabel = new QLabel(this);
    nameLabel = new QLabel(this);
    contentsLabel = new QLabel(this);
    timeLabel = new QLabel(this);
    layout = new QGridLayout(this);
    avatarLabel->setFixedSize(30,30);
    nameLabel->setText(Account->username);
    contentsLabel->setText(message);
    timeLabel->setText(time+" "+date);          //姑且设置文字内容
    layout->addWidget(avatarLabel,0,0,2,2);
    layout->addWidget(nameLabel,0,2,1,16);
    layout->addWidget(contentsLabel,1,2,1,24);
    layout->addWidget(timeLabel,0,6,1,8);
    this->setLayout(layout);

    nameLabel->setFont(QFont("楷体",10,QFont::Bold));
    timeLabel->setFont(QFont("黑体",8,QFont::Bold));
    contentsLabel->setFont(QFont("黑体",8));

    QImage *cAvatar = new QImage();
    cAvatar->load(":/new/prefix1/resources/sessionAvatarP.jpg");
    QPixmap pixmap = QPixmap::fromImage(*cAvatar);
    int width = avatarLabel->width();
    int height = avatarLabel->height();
    QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    avatarLabel->setPixmap(fitpixmap);              //绘制对话头像
}
