#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include <Qstring>
#include <QLabel>
#include <QScrollArea>
#include <QGridLayout>
#include <currentaccount.h>
#include <QFont>
#include <QListWidget>
#include <sessionlistitem.h>
#include <QDebug>
#include <settingswidget.h>
#include <QImage>
#include <QIcon>
#include "searchcontactswidget.h"
#include "contactswidget.h"
#include <QCloseEvent>
#include <QMessageBox>
#include "sessionlistitemofmain.h"

extern QTcpSocket *socketOfCyno;
extern QString mainWidgetBack;
extern QString sessionWidgetBack;

class mainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit mainWidget(QWidget *parent = 0);
    mainWidget(currentAccount *cAccount);
    currentAccount *cAccount=NULL;
    QLabel *avatar = NULL;
    QLabel *username = NULL;
    QLabel *signature = NULL;
    QPushButton *settings = NULL;
    QPushButton *search = NULL;
    QPushButton *contacts = NULL;       //定义一系列位于主界面的标签以及按钮
    QGridLayout *Layout = NULL;         //定义上方与下方的栅格布局
    QListWidget *listWidget;
    QFont fontOfUsername;
    QImage *cAvatar = NULL;
    mainWidget *mainWidgetOfCyno = this;    //定义一个指向自己的指针
    QTcpSocket *socketOfMain ;
    currentAccount *sender = NULL;
    void closeEvent(QCloseEvent *event);    //重写关闭事件函数
    void paintEvent(QPaintEvent *);         //绘制背景用的函数
signals:

public slots:
    void newSettingsWidget();
    void newSearchContactsWidget();
    void newContactsWidget();
    void readData();
};

#endif // MAINWIDGET_H

//这是主窗口
