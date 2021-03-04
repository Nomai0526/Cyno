#ifndef SEARCHRESULTITEM_H
#define SEARCHRESULTITEM_H

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
#include <QImage>


class searchResultItem : public QWidget
{
    Q_OBJECT
public:
    searchResultItem(QString cAccount,QString avatar,QString account,QString username);
    QString account;
    QString cAccount;
    QLabel *avatarLabel = NULL;
    QLabel *accountLabel = NULL;
    QLabel *usernameLabel = NULL;
    QPushButton *addContacts = NULL;
    QGridLayout *layout = NULL;
    QTcpSocket *addContactsSocket = NULL;
signals:

public slots:
    void addContactsSlot();
};

#endif // SEARCHRESULTITEM_H

//这是搜索结果的条目窗口
