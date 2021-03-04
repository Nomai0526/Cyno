#ifndef CLIENTSQLADMIN_H
#define CLIENTSQLADMIN_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QSqlTableModel>
#include <currentaccount.h>


class clientSqlAdmin
{
public:
    clientSqlAdmin();
    clientSqlAdmin(currentAccount *cAccount);
    QSqlDatabase CynoClientSql;
    void addMessage(QString message);           //加入消息记录用的
};

#endif // CLIENTSQLADMIN_H

//这是客户端数据库管理文件
