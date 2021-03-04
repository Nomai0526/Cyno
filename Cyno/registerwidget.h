#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include <Qstring>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QIntValidator>
#include <QPainter>


class registerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit registerWidget(QWidget *parent = 0);
    QString realAccount;
    QString realPassword;               //用于保存账号和密码，出于简单暂时只能保存一个
    QLineEdit *accountLine=NULL;
    QLineEdit *passwordLine=NULL;       //定义账号和密码框
    QPushButton *registerButton=NULL;
    QPushButton *cancelButton=NULL;       //定义登陆和注册按钮
    QDialog *loginFailure=NULL;         //定义登陆失败弹窗
    QDialog *loginSuccess=NULL;
    QGridLayout *layout=NULL;           //定义栅格布局
    void paintEvent(QPaintEvent* event);
public slots:
    void registerslot();

signals:

public slots:
};

#endif // REGISTERWIDGET_H

//这是注册页面的类
