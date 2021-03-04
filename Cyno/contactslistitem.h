#ifndef CONTACTSLISTITEM_H
#define CONTACTSLISTITEM_H

#include <QWidget>
#include <mainwidget.h>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include <Qstring>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QTime>
#include <QApplication>
#include <currentaccount.h>
#include <clientsqladmin.h>
#include <QAction>
#include "searchresultitem.h"
#include <QListWidgetItem>
#include <currentaccount.h>
#include <sessionwidget.h>
#include <QPointer>


class contactsListItem : public QWidget
{
    Q_OBJECT
public:
    explicit contactsListItem(QWidget *parent = 0);
    contactsListItem(currentAccount *cAccount,QString avatar,QString account,QString username,QString online);
    QString account;
    QString username;
    QLabel *avatarLabel = NULL;
    QLabel *accountLabel = NULL;
    QLabel *usernameLabel = NULL;
    QLabel *onlineLabel = NULL;
    QPushButton *deleteContacts = NULL;
    QPushButton *sendMessage= NULL;
    QGridLayout *layout = NULL;
    QTcpSocket *ContactsSocket = NULL;
    currentAccount *cAccount = NULL;
    currentAccount *receiver = NULL;
signals:

public slots:
    void deleteContactsSlot();
    void sendMessageSlot();
};

#endif // CONTACTSLISTITEM_H

//这个是联系人列表中的条目窗口
