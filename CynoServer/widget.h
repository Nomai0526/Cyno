#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <string>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QMap>
#include <QStringList>
#include <sqladmin.h>

class Widget : public QWidget
{
    Q_OBJECT
public:
    QStringList infoList;
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    int numberOfConnectedClient=0;
    QStringList *accountToIP=NULL;
    QLineEdit *edtIP=NULL;
    QLineEdit *edtPort=NULL;
    QPushButton *connectButton=NULL;
    QTextEdit *textReceive=NULL;
    QTcpServer *tcpServer=NULL;
    QList<QTcpSocket*> tcpClient;
    QTcpSocket *currentClient=NULL;
    QGridLayout *layout =NULL;
    sqlAdmin *sqladmin=NULL;

private slots:
    void NewConnectionSlot();
    void disconnectedSlot();
    void ReadData();
    void on_btnConnect_clicked();
};

#endif // WIDGET_H

//这是服务端主文件
