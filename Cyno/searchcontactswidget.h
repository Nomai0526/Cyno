#ifndef SEARCHCONTACTSWIDGET_H
#define SEARCHCONTACTSWIDGET_H

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



class searchContactsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit searchContactsWidget(QWidget *parent = 0);
             searchContactsWidget(currentAccount *cAccount);
             QPushButton *search = NULL;
             QLineEdit *key = NULL;
             currentAccount *cAccount = NULL;
             QGridLayout *layout = NULL;
             QListWidget *resultsList = NULL;
             QTcpSocket *searchSocket = NULL;
             void paintEvent(QPaintEvent *);
signals:

public slots:
             void searchslot();
             void readData();
};

#endif // SEARCHCONTACTSWIDGET_H

//这是搜索联系人窗口
