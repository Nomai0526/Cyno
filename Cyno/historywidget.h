#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QObject>
#include <QWidget>
#include <currentaccount.h>
#include <QListWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QSqlTableModel>
#include <QGridLayout>
#include "sessionlistitem.h"
#include <QStringList>


class historyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit historyWidget(QWidget *parent = 0);
        historyWidget(currentAccount *cAccount,currentAccount *receiver);
        QListWidget *history = NULL;
        QSqlDatabase CynoClientSql ;
        QGridLayout *layout =NULL;
        currentAccount *cAccount = NULL;
signals:

public slots:
};

#endif // HISTORYWIDGET_H

//这个类是历史窗口类
