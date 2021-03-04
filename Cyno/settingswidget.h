#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <currentaccount.h>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include "loginwidget.h"

extern QString mainWidgetBack;
extern QString sessionWidgetBack;

class settingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit settingsWidget(QWidget *parent = 0);
    settingsWidget(currentAccount *cAccount);
    QPushButton *changeAvatar = NULL;
    QPushButton *changeUserName = NULL;
    QPushButton *changeSignature = NULL ;
    QPushButton *changePassword = NULL;
    QPushButton *changeSessionBack = NULL;
    QLineEdit *newUserName=NULL;
    QLineEdit *newSignature = NULL;
    QLineEdit *newPassword = NULL;
    QGridLayout *layout = NULL;
    currentAccount *cAccount;
    QTcpSocket *socketOfSettings = NULL;
    void paintEvent(QPaintEvent *);
signals:

public slots:
    void changeAvatarSlot();
    void changeUserNameSlot();
    void changeSignatureSlot();
    void changePasswordSlot();
    void changeSessionBackSlot();
    void readData();

};

#endif // SETTINGSWIDGET_H

//这个是设置窗口
