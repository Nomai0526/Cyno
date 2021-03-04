


#include "clientsqladmin.h"

clientSqlAdmin::clientSqlAdmin(currentAccount *cAccount)
{
    CynoClientSql = QSqlDatabase::addDatabase("QSQLITE");
    CynoClientSql.setDatabaseName(QString("./CynoClientOf%1.db").arg(cAccount->account));
    //打开数据库或建立数据库
    if (!CynoClientSql.open())
    {
        qDebug() << "Connect to Sqlite error: " << CynoClientSql.lastError().text();
        exit(128);
    }
    //创建一个消息记录表
    QSqlQuery createTableQuery(CynoClientSql);
    QString sql("CREATE TABLE message("
                "num integer primary key autoincrement, "
                "receiver text not null, "
                "sender text not null, "
                "content text not null, "
                "time text not null)");
      createTableQuery.exec(sql);
}

void clientSqlAdmin::addMessage(QString message)    //发过来的信息格式应该是"接收人，发送人，内容，日期时间"
{
    QStringList info = message.split(" ");          //分段读取传进来的信息，表的创建工作应该在登录时已经完成
    QSqlTableModel model;
    model.setTable("message");
    QSqlRecord record = model.record();             //设置各字段键值
    record.setValue("receiver", info.at(0));
    record.setValue("sender", info.at(1));
    record.setValue("content", info.at(2));
    record.setValue("time", info.at(3)+" "+info.at(4));

    model.insertRecord(-1, record);
}

