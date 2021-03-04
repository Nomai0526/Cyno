#include "mainwidget.h"

mainWidget::mainWidget(QWidget *parent) : QWidget(parent)
{

}

mainWidget::mainWidget(currentAccount *cAccount)
{
    fontOfUsername.setFamily("黑体");
    fontOfUsername.setBold(true);
    fontOfUsername.setPixelSize(20);    //配置昵称的字体为黑体，加粗，20像素
    this->cAccount = cAccount;
    this->setWindowTitle("Cyno");
    this->setFixedSize(320,900);           //设置窗口的默认大小和最大宽度
    avatar = new QLabel("avatar",this);     //之后将这里改为人物头像的地址
    username = new QLabel("username",this);
    signature = new QLabel("signature",this);
    settings = new QPushButton("  设置   ",this);
    search = new QPushButton("   搜索   ",this);
    contacts = new QPushButton("   好友   ",this);   //设置三个按钮
    avatar->setFixedSize(60,60);
    username->setFixedSize(200,50);
    signature->setFixedSize(3000,50);
    settings->setFixedHeight(30);
    search->setFixedHeight(30);
    contacts->setFixedHeight(30);
    username->setFont(fontOfUsername);
    signature->setFont(QFont("黑体"));
    avatar->move(20,0);
    username->move(110,0);
    signature->move(110,50);            //这里出于需求没有用布局管理器而是手动布局
    settings->move(0,100);
    search->move(100,100);
    contacts->move(210,100);             //按钮手动布局
    username->setText(cAccount->username);
    signature->setText(cAccount->signature);

    cAvatar = new QImage();
    if(cAccount->avatar==QString("default"))
        cAvatar->load(":/new/prefix1/resources/defaultAvatarP.jpg");
    else
        cAvatar->load(cAccount->avatar);
    QPixmap pixmap = QPixmap::fromImage(*cAvatar);
    int width = avatar->width();
    int height = avatar->height();
    QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    avatar->setPixmap(fitpixmap);       //如果设置过背景，则绘制目标背景，否则绘制默认背景

    listWidget = new QListWidget(this);
    listWidget->setFixedSize(320,780);
    listWidget->move(0,130);
    listWidget->setStyleSheet("background-color:transparent");
    listWidget->setFrameShape(QListWidget::NoFrame);        //消息列表设置

    avatar->setStyleSheet("min-width:100px;max-width:100px;min-height:100px;max-height: 100px;border-radius: 50px;border-width: 0 0 0 0;");

    settings->setStyleSheet("border:1px groove gray;border-radius:10px;padding:2px 4px;background-color: white");
    search->setStyleSheet("border:1px groove gray;border-radius:10px;padding:2px 4px;background-color: white");
    contacts->setStyleSheet("border:1px groove gray;border-radius:10px;padding:2px 4px;background-color: white");

    settings->setFont(QFont("楷体",10,QFont::Bold));
    search->setFont(QFont("楷体",10,QFont::Bold));
    contacts->setFont(QFont("楷体",10,QFont::Bold));

    connect(settings,SIGNAL(clicked(bool)),this,SLOT(newSettingsWidget()));
    connect(search,SIGNAL(clicked(bool)),this,SLOT(newSearchContactsWidget()));
    connect(contacts,SIGNAL(clicked(bool)),this,SLOT(newContactsWidget()));
    connect(socketOfCyno,SIGNAL(readyRead()),this,SLOT(readData()));
}

void mainWidget::newSettingsWidget()    //按下设置键即打开新设置窗口
{
    settingsWidget *settings = new settingsWidget(cAccount);
    settings->show();
}
void mainWidget::newSearchContactsWidget()      //按下搜索即打开新搜索窗口
{
    searchContactsWidget *searchWidget  = new searchContactsWidget(cAccount);
    searchWidget->show();
}
void mainWidget::newContactsWidget()            //按下联系人按钮即打开新联系人窗口
{
    contactsWidget *acontactsWidget = new contactsWidget(cAccount);
    acontactsWidget->show();
}
void mainWidget::closeEvent(QCloseEvent *event)     //窗口关闭事件
{
    socketOfCyno->write("online 1 false");              //发送下线信号
}
void mainWidget::readData()
{
    QByteArray buffer;
    sender = new currentAccount();
    buffer = socketOfCyno->readAll();
    QString info = QByteArray(buffer);
    QStringList list;
    list = info.split(" ");
    sender->username = list.at(6);
    if(list.at(0)=="messageTransport")
    {
        sessionListItemOfMain *anSessionListItem = new sessionListItemOfMain(this->sender,list.at(3),list.at(4),list.at(5));
        QListWidgetItem *item = new QListWidgetItem(listWidget);
        item->setSizeHint(QSize(0,90));
        listWidget->setItemWidget(item,anSessionListItem);   //读取一条信息，建立一个特定的窗口对象，并将其设为一项
    }
}

void mainWidget::paintEvent(QPaintEvent *)
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
