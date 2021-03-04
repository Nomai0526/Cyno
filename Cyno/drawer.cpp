#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>

Drawer::Drawer(QWidget *parent) :
    QToolBox(parent)
{
    w=new Widget();
    setWindowTitle("My QQ");

    btn1=new QToolButton();
    btn1->setText("张三");//设置QToolButton按钮标题
    btn1->setIcon(QPixmap("1.jpg"));//设置QToolButton的图像
    btn1->setIconSize(QPixmap("1.jpg").size());//设置QToolButton的大小和图像一致
    btn1->setAutoRaise(true);//设置QToolButton按钮自动弹起
    btn1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置文字在图片的旁边

    btn2=new QToolButton();
    btn2->setText("李四");//设置QToolButton按钮标题
    btn2->setIcon(QPixmap("2.jpg"));//设置QToolButton的图像
    btn2->setIconSize(QPixmap("2.jpg").size());//设置QToolButton的大小和图像一致
    btn2->setAutoRaise(true);//设置QToolButton按钮自动弹起
    btn2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置文字在图片的旁边

    btn3=new QToolButton();
    btn3->setText("王五");//设置QToolButton按钮标题
    btn3->setIcon(QPixmap("3.jpg"));//设置QToolButton的图像
    btn3->setIconSize(QPixmap("3.jpg").size());//设置QToolButton的大小和图像一致
    btn3->setAutoRaise(true);//设置QToolButton按钮自动弹起
    btn3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置文字在图片的旁边

    btn4=new QToolButton();
    btn4->setText("赵六");//设置QToolButton按钮标题
    btn4->setIcon(QPixmap("4.jpg"));//设置QToolButton的图像
    btn4->setIconSize(QPixmap("4.jpg").size());//设置QToolButton的大小和图像一致
    btn4->setAutoRaise(true);//设置QToolButton按钮自动弹起
    btn4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置文字在图片的旁边

    QGroupBox *gbox1=new QGroupBox();
    QVBoxLayout *vblay1=new QVBoxLayout(gbox1);
    vblay1->setMargin(10);//设置各控件的间距
    vblay1->setAlignment(Qt::AlignHCenter);//设置控件位置居中
    vblay1->addWidget(btn1);
    vblay1->addWidget(btn2);
    vblay1->addStretch();//加一个占位控件

    QGroupBox *gbox2=new QGroupBox();
    QVBoxLayout *vblay2=new QVBoxLayout(gbox2);
    vblay2->setMargin(10);//设置各控件的间距
    vblay2->setAlignment(Qt::AlignHCenter);//设置控件位置居中
    vblay2->addWidget(btn3);
    vblay2->addWidget(btn4);
    vblay2->addStretch();

    this->addItem((QWidget *)gbox1,tr("我的好友"));
    this->addItem((QWidget *)gbox2,tr("陌生人"));

    connect(btn1,SIGNAL(clicked()),this,SLOT(showMyWidget()));
    connect(btn2,SIGNAL(clicked()),this,SLOT(showMyWidget()));
    connect(btn3,SIGNAL(clicked()),this,SLOT(showMyWidget()));
    connect(btn4,SIGNAL(clicked()),this,SLOT(showMyWidget()));

}

void Drawer::showMyWidget()
{
    w->show();
}
