#ifndef CYNOCLIENT_H
#define CYNOCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QGridLayout>

class CynoClient : public QWidget
{
    Q_OBJECT
public:
    explicit CynoClient(QWidget *parent = 0);
    QLineEdit *edtIP=NULL;
    QLineEdit *edtPort=NULL;
    QPushButton *connectButton=NULL;
    QPushButton *sendButton=NULL;
    QTextEdit *textReceive=NULL;
    QTextEdit *textSend=NULL;
    QTcpServer *tcpServer=NULL;
    QTcpSocket *currentClient=NULL;
    QComboBox *cbxConnection =NULL;
    QGridLayout *layout =NULL;
private:
    QTcpSocket *tcpClient=NULL;

private slots:
    //客户端槽函数
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

    void on_btnConnect_clicked();
    void on_btnSend_clicked();
    void on_pushButton_clicked();
signals:

public slots:
};

#endif // CYNOCLIENT_H
