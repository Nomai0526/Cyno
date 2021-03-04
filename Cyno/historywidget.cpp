



#include "historywidget.h"

historyWidget::historyWidget(QWidget *parent) : QWidget(parent)
{

}
historyWidget::historyWidget(currentAccount *cAccount, currentAccount *receiver)
{
    this->cAccount = cAccount;
    this->resize(500,300);
    history = new QListWidget();
    layout = new QGridLayout(this);
    layout->addWidget(history,0,0,1,1);
    this->setLayout(layout);

    CynoClientSql = QSqlDatabase::addDatabase("QSQLITE");
    CynoClientSql.setDatabaseName(QString("./CynoClientOf%1.db").arg(cAccount->account));
    //打开数据库或建立数据库
    if (!CynoClientSql.open())
    {
        qDebug() << "Connect to Sqlite error: " << CynoClientSql.lastError().text();
        exit(128);
    }
    QSqlQuery query;    //这里的qaccou是信息的第二段文字，即为账号的字符串形式
    query.exec(QString("SELECT * FROM message where receiver = '%1'and sender = '%2' ").arg(receiver->username).arg(cAccount->username));       //在数据库中多条件检索以找到目标
    while(query.next())
    {
        QStringList temp = query.value(4).toString().split(" ");
        sessionListItem *anSessionListItem = new sessionListItem(this->cAccount,query.value(3).toString(),temp.at(0),temp.at(1));
        QListWidgetItem *item = new QListWidgetItem(history);
        //        contactsListItem *anContactsListItem = new contactsListItem(QString::number(cAccount->account),anContact.at(1),anContact.at(0),anContact.at(2));
        history->addItem(item);
        item->setSizeHint(QSize(0,90));
        history->setItemWidget(item,anSessionListItem);
    }
}
