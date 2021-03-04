#include "sqladmin.h"

sqlAdmin::sqlAdmin()
{
    CynoServerSql = QSqlDatabase::addDatabase("QSQLITE");
    CynoServerSql.setDatabaseName("../CynoServer/CynoServer.db");
    //打开数据库
    if (!CynoServerSql.open())
    {
        qDebug() << "Connect to Sqlite error: " << CynoServerSql.lastError().text();
        exit(128);
    }
    newUserInfo(CynoServerSql);
}
sqlAdmin::~sqlAdmin()
{

}
void sqlAdmin::newUserInfo(QSqlDatabase CynoServerSql)  //创建用户信息表
{
    //创建一个用户信息表
    QSqlQuery createTableQuery(CynoServerSql);
    QString sql("CREATE TABLE userinfo("
                "account integer primary key autoincrement, "
                "password text not null, "
                "avatar text not null, "
                "username text not null, "
                "signature text not null, "
                "messageList text not null,"
                "contacts text not null,"
                "online integer not null)");

    //把sql字符串传递到函数里执行
    createTableQuery.exec(sql);
    //插入数据
}
void sqlAdmin::addUserInfo(QSqlDatabase CynoServerSql,QStringList list) //添加用户信息
{
    QString qsql = QString("CREATE TABLE contactOf%1("
                           "account integer primary key autoincrement, "
                           "avatar text not null, "
                           "username text not null, "
                           "signature text not null)").arg(list.at(1));
    QString ssql = qsql.toUtf8();
    QSqlQuery createTableQuery(CynoServerSql);                      //创立联系人表格 格式为账号 头像 昵称 签名
    QString sql(ssql);
    createTableQuery.exec(sql);

    QSqlTableModel model;            //这里创建用户信息
    QString qaccount=list.at(1);
    int account =qaccount.toInt();
    model.setTable("userInfo");
    QSqlRecord record = model.record();     //设置各字段键值
    record.setValue("account", account);
    record.setValue("password", list.at(2));
    record.setValue("avatar", "default");
    record.setValue("username", QString::number(account));
    record.setValue("signature", "default");
    record.setValue("messageList", "default");
    record.setValue("contacts", "");
    record.setValue("online",0);
    model.insertRecord(-1, record);     //使用record向表中添加数据
}

QString sqlAdmin::searchUserInfo(QSqlDatabase CynoServerSql,QStringList list)   //添加用户的一系列信息，同时为其创立一个联系人表格
{
    QSqlQuery query;
    QString info;
    QString qaccount=list.at(1);        //这里的qaccou是信息的第二段文字，即为账号的字符串形式
    int account =qaccount.toInt();      //转为int
    query.exec(QString("SELECT * FROM userinfo where account = '%1' ").arg(account));   //在数据库中查询account的条目
    while(query.next())             //query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        for(int i=0;i<7;i++)
        {
            info =info+query.value(i).toString()+" ";        //value(1)即为密码
        }
    }
    return info;            //返回查询到的信息
}
QString sqlAdmin::searchNewContact(QSqlDatabase CynoServerSql,QStringList list)         //查询用户的函数
{
    QSqlQuery query;
    QString info;
    QString qaccount=list.at(1);        //这里的qaccou是信息的第二段文字，即为账号的字符串形式
    int account =qaccount.toInt();      //转为int
    query.exec(QString("SELECT * FROM userinfo where account = '%1' ").arg(account));
    if(query.next())
    info =query.value(0).toString()+" "+query.value(2).toString()+" "+query.value(3).toString()+" "+query.value(4).toString()+"#";        //发送的信息格式是 账号 头像 昵称 签名
    query.exec(QString("SELECT * FROM userinfo where username = '%1' ").arg(qaccount));   //这是通过昵称搜索人
    while(query.next())             //这里可能不止一个结果
    {
            info =info+query.value(0).toString()+" "+query.value(2).toString()+" "+query.value(3).toString()+" "+query.value(4).toString()+"#"; //每条之间用#分割
    }
    return info;            //返回查询到的信息
}

void sqlAdmin::changeUserInfo(QSqlDatabase CynoServerSql,QStringList list)              //改变用户信息的函数
{
    QSqlQuery query;                    //这里像以上函数一样按账号检索数据库，检索到目标更改相应项目即可
    QString qaccount=list.at(1);        //这里的qaccout是信息的第二段文字，即为账号的字符串形式
    int account =qaccount.toInt();      //转为int
    if(list.at(2)==QString("avatar"))
    {
        query.exec(QString("update userinfo set avatar = '%1' where account = '%2' ").arg(list.at(3)).arg(account));   //更改头像
    }
    if(list.at(2)==QString("username"))
    {
        query.exec(QString("update userinfo set username = '%1' where account = '%2' ").arg(list.at(3)).arg(account));   //更改昵称
    }
    if(list.at(2)==QString("signature"))
    {
        query.exec(QString("update userinfo set signature = '%1' where account = '%2' ").arg(list.at(3)).arg(account));   //更改签名
    }
    if(list.at(2)==QString("password"))
    {
        query.exec(QString("update userinfo set password = '%1' where account = '%2' ").arg(list.at(3)).arg(account));   //更改密码
    }                                               //根据信息的内容更改不同的信息
}

void sqlAdmin::addContacts(QSqlDatabase CynoServerSql,QStringList list)     //添加联系人的函数
{
    QSqlQuery query;
    QString info;
    QString qaccount=list.at(1);        //这里的qaccou是信息的第二段文字，即为账号的字符串形式
    int account =qaccount.toInt();      //转为int
    QString qcontact=list.at(2);        //这里是信息的第三段文字，即为新联系人的字符串形式
    query.exec(QString("SELECT * FROM userinfo where account = '%1' ").arg(account));   //在数据库中查询account的条目
    while(query.next())             //query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QString preContacts = query.value(6).toString();        //读取旧列表
        QString newContacts = preContacts +" " + qcontact;          //新列表即为旧列表加新联系人
        query.exec(QString("update userinfo set contacts = '%1' where account = '%2' ").arg(newContacts).arg(account));    //更改联系人列表
    }
}
void sqlAdmin::setOnlineState(QSqlDatabase CynoServerSql,QStringList list)  //设置在线状态的函数
{
    QSqlQuery query;
    QString info;
    QString qaccount=list.at(1);        //这里的qaccou是信息的第二段文字，即为账号的字符串形式
    int account =qaccount.toInt();      //转为int
//    qDebug()<<list.at(0)<<list.at(1)<<list.at(2);
    query.exec(QString("SELECT * FROM userinfo where account = '%1' ").arg(account));   //在数据库中查询account的条目
    while(query.next())             //判断信息设置在线状态
    {
        if(list.at(2)==QString("true"))
        query.exec(QString("update userinfo set online = 1 where account = '%1' ").arg(account));    //将在线状态设为在线
        if(list.at(2)==QString("false"))
        query.exec(QString("update userinfo set online = 0 where account = '%1' ").arg(account));    //将在线状态设为离线
    }
}
QString sqlAdmin::showContacts(QSqlDatabase CynoServerSql,QStringList list)             //查询联系人的函数
{
    QSqlQuery query;
    QString info;
    QString qaccount=list.at(1);        //这里的qaccou是信息的第二段文字，即为账号的字符串形式
    int account =qaccount.toInt();      //转为int
    query.exec(QString("SELECT * FROM userinfo where account = '%1' ").arg(account));   //在数据库中查询account的条目
    while(query.next())             //query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QString contacts = query.value(6).toString();
        QStringList contactsList = contacts.split(" ");         //读取联系人列表
        for(int i = 0;i<contactsList.length();i++)
        {
            if(contactsList.at(i)!="")
            {
                QSqlQuery query2;
                QString qaccount2=contactsList.at(i);        //这里的qaccou是信息的第二段文字，即为账号的字符串形式
                int account2 =qaccount2.toInt();      //转为int
                query2.exec(QString("SELECT * FROM userinfo where account = '%1' ").arg(account2));     //逐个查询
                while(query2.next())
                {
                    info =info+query2.value(0).toString()+" "+query2.value(2).toString()+" "+query2.value(3).toString()+" "+query2.value(4).toString()+" "+query2.value(7).toString()+"#";
                }
            }
        }
    }
    return info;                //返回查询到的信息
}

void sqlAdmin::changeContacts(QSqlDatabase CynoServerSql,QStringList list)      //更改联系人的函数
{
    QSqlQuery query;
    QString info;
    QString qaccount=list.at(1);        //这里的qaccou是信息的第二段文字，即为账号的字符串形式
    int account =qaccount.toInt();      //转为int
    QString qcontact=list.at(2);        //这里是信息的第三段文字，即为要删除的联系人的字符串形式
    query.exec(QString("SELECT * FROM userinfo where account = '%1' ").arg(account));   //在数据库中查询account的条目
    while(query.next())             //query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QString preContacts = query.value(6).toString();        //读取旧列表
        QStringList contactsList = preContacts.split(" ");
        QString newContacts ;          //新列表即为旧列表去除该联系人
        for(int i =0; i<contactsList.length();i++)
        {
            if(contactsList.at(i)==qcontact)
                continue;
            else newContacts = newContacts+contactsList.at(i)+" ";          //以此达到删除该联系人的效果
        }
        query.exec(QString("update userinfo set contacts = '%1' where account = '%2' ").arg(newContacts).arg(account));    //更改联系人列表
    }
}

