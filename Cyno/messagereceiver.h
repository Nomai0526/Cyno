#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

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
#include <clientsqladmin.h>

extern QTcpSocket *socketOfCyno;

class messageReceiver :public QObject
{
    Q_OBJECT
public:
    messageReceiver();
    messageReceiver(currentAccount *cAccount);
//    QTcpSocket *messageReceiverSocket;
//    QString receivedMessage;
//    QString receivedMessage[100];
//    static int numberOfReceivedMessage=0;

private slots:
//    void receivingOfflineMessage(int numberOfReceivedMessage);
    void receivingMessage(currentAccount *cAccount);
};

#endif // MESSAGERECEIVER_H
