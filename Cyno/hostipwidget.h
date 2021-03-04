#ifndef HOSTIPWIDGET_H
#define HOSTIPWIDGET_H

#include <QWidget>
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
#include"loginwidget.h"

extern QString hostIP;

class hostIPWidget : public QWidget
{
    Q_OBJECT
public:
    explicit hostIPWidget(QWidget *parent = 0);
    QLineEdit *IPEdit = NULL;
    QPushButton *next = NULL;
    QGridLayout *layout = NULL;
signals:

public slots:
        void getIP();
};


#endif // HOSTIPWIDGET_H
