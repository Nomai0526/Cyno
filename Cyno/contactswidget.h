#ifndef CONTACTSWIDGET_H
#define CONTACTSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <mainwidget.h>
#include <QListWidget>
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
#include "contactslistitem.h"
#include <QListWidgetItem>


class contactsWidget : public QWidget
{
        Q_OBJECT
public:
        explicit contactsWidget(QWidget *parent);
        contactsWidget(currentAccount *cAccount);
        QPushButton *search = NULL;
        QLineEdit *key = NULL;
        currentAccount *cAccount = NULL;
        QGridLayout *layout = NULL;
        QListWidget *contactsList = NULL;
        QTcpSocket *contactsSocket = NULL;
        QStringList *contactsNumber = NULL;     //这个是查找联系人的时候用的
        void paintEvent(QPaintEvent *);
public slots:
        void readData();
        void searchSlot();
};

#endif // CONTACTSWIDGET_H

//这个是联系人列表窗口
