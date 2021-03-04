#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <registerwidget.h>
#include <mainwidget.h>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include <Qstring>
#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QTime>
#include <QApplication>
#include <currentaccount.h>
#include <QPainter>

extern QTcpSocket *socketOfCyno;

class loginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit loginWidget(QWidget *parent = 0);
    QString realAccount;
    QString realPassword;               //用于保存账号和密码，出于简单暂时只能保存一个
    QLineEdit *accountLine=NULL;
    QLineEdit *passwordLine=NULL;       //定义账号和密码框
    QPushButton *registerButton=NULL;
    QPushButton *loginButton=NULL;       //定义登陆和注册按钮
    QDialog *loginFailure=NULL;         //定义登陆失败弹窗
    QGridLayout *layout=NULL;           //定义栅格布局
    currentAccount *cAccount =NULL;
    int numberOfLoginSuccess=0;         //这个参数用于记录登录成功的次数，用以关闭读取缓存区的函数
    void paintEvent(QPaintEvent* event);
public slots:
    void readAccountAndPassword();
    void registerPageAppear();
    void ReadData();

signals:
};

#endif // LOGINWIDGET_H

//这是登录窗口的类
