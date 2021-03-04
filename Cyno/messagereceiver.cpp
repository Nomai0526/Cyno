#include "messagereceiver.h"

messageReceiver::messageReceiver()
{

}

messageReceiver::messageReceiver(currentAccount *cAccount)
{
//    socketOfCyno = new QTcpSocket();
//    socketOfCyno->connectToHost("192.168.33.141", 8000);
//    QString loginSuccessMessage;
//    loginSuccessMessage = "searchOfflineMessage "+QString::number(cAccount->account);
//    socketOfCyno->write(loginSuccessMessage.toUtf8());

//    connect(socketOfCyno,SIGNAL(readyRead()),this,SLOT(receivingMessage()));


}

//void messageReceiver::receivingMessage(currentAccount *cAccount)
//{
//    QByteArray buffer = socketOfCyno->readAll();
//    receivedMessage=buffer;
//    QString message = buffer;
//    clientSqlAdmin *temp = new clientSqlAdmin(cAccount) ;
//    temp->addMessage(message);
//}

//void messageReceiver::receivingOfflineMessage(int numberOfReceivedMessage)
//{
//    QByteArray buffer = socketOfCyno->readAll();
//    receivedMessage[numberOfReceivedMessage]=buffer;
//    numberOfReceivedMessage++;
//    if(numberOfReceivedMessage=100)
//        numberOfReceivedMessage=0;

//}
