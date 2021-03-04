#include "widget.h"
#include "loginwidget.h"
#include "registerwidget.h"
#include "cynoclient.h"
#include <QApplication>
#include <currentaccount.h>
#include <mainwidget.h>
#include <toolbox.h>
#include <drawer.h>
#include <sessionwidget.h>
#include <clientsqladmin.h>
#include <settingswidget.h>
#include <searchcontactswidget.h>
#include <searchresultitem.h>

QTcpSocket *socketOfCyno;  //整个程序很多地方都要共用，所以放在全局变量的位置
QString mainWidgetBack;
QString sessionWidgetBack;

int main(int argc, char *argv[])
{
      QApplication a(argc, argv);
      socketOfCyno = new QTcpSocket();
      socketOfCyno->connectToHost("192.168.33.141", 8000);
    loginWidget w;
    w.show();
    return a.exec();
}
