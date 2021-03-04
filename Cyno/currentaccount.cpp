
#include "currentaccount.h"
currentAccount::currentAccount()
{
    account=0;
    passWord="default";
    avatar="default";
    username="default";
    signature="default";
    messageList="default";
    contacts="default";
}                           //默认的账号对象

currentAccount::currentAccount(QStringList list)
{
    account=list.at(0).toInt();
    passWord=list.at(1);
    avatar=list.at(2);
    username=list.at(3);
    signature=list.at(4);
    messageList=list.at(5);
    contacts=list.at(6);    //读取从服务器传来的各种信息而构造的账号对象
}
currentAccount::~currentAccount()
{

}
