#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include <QString>
#include <QStringList>

class currentAccount
{
public:
    currentAccount();
    currentAccount(QStringList list);
    ~currentAccount();
    int account;    //个人信息按照 账号，密码，头像，昵称，签名，消息记录，联系人 排序
    QString passWord;
    QString avatar;
    QString username;
    QString signature;
    QString messageList;
    QString contacts;
    //定义一个账号的各种信息，有些内容姑且用Qstring格式代替
};

#endif // CURRENTACCOUNT_H

//这个类是一个账号类
