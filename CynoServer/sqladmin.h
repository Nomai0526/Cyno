#ifndef SQLADMIN_H
#define SQLADMIN_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QSqlTableModel>


class sqlAdmin
{
public:
    QSqlDatabase CynoServerSql;
    sqlAdmin();
    ~sqlAdmin();
    void newUserInfo(QSqlDatabase CynoServerSql);     //创建新的账户数据表，在一个服务器上只需要启动一次
    void addUserInfo(QSqlDatabase CynoServerSql,QStringList list);     //注册用的
    QString searchUserInfo(QSqlDatabase CynoServerSql,QStringList list);  //登录用的
    QString searchNewContact(QSqlDatabase CynoServerSql,QStringList list);  //查找联系人用的，为了方便与上一个区分，实际应该是差不多的
    void changeUserInfo(QSqlDatabase CynoServerSql,QStringList list);  //改密码，头像，签名，昵称用的
    void setOnlineState(QSqlDatabase CynoServerSql,QStringList list);   //修改登录状态
    void addContacts(QSqlDatabase CynoServerSql,QStringList list);           //添加联系人用的
    QString showContacts(QSqlDatabase CynoServerSql,QStringList list);      //显示联系人用的
    void changeContacts(QSqlDatabase CynoServerSql,QStringList list);      //修改联系人用的
};

#endif // SQLADMIN_H

//这是服务端数据库操作文件
