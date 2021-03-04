#ifndef SESSIONWIDGET_H
#define SESSIONWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <QStringList>
#include <currentaccount.h>
#include <QTime>
#include <QDate>
#include <QPainter>
#include "sessionlistitem.h"
#include <clientsqladmin.h>
#include "historywidget.h"

extern QString sessionWidgetBack;

class sessionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit sessionWidget(QWidget *parent = 0);
    sessionWidget(currentAccount *cAccount,currentAccount *receiver);       //这个receiver是对话人
    int closedNumber = 0;
    currentAccount *cAccount=NULL;
    currentAccount *receiver=NULL;
    QPushButton *historyButton = NULL;
    QPushButton *clearButton = NULL;
    QPushButton *sendMessageButton = NULL;
    QListWidget *messageList = NULL;
    QTextEdit *messageToSend =NULL;
    QTcpSocket *socketOfSesssion = NULL;
    QGridLayout *Layout=NULL;
    clientSqlAdmin *cynoSql = NULL;
    void paintEvent(QPaintEvent *);
public slots:
    void sendMessage();
    void ReadData();
    void showHistory();
signals:


};

#endif // SESSIONWIDGET_H

//这个是对话窗口
