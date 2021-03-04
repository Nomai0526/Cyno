#ifndef SESSIONLISTITEMOFMAIN_H
#define SESSIONLISTITEMOFMAIN_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <currentaccount.h>

class sessionListItemOfMain : public QWidget
{
    Q_OBJECT
public:
    explicit sessionListItemOfMain(QWidget *parent = 0);
    sessionListItemOfMain(currentAccount *Account,QString message,QString date,QString time);
    QLabel *avatarLabel=NULL;
    QLabel *nameLabel=NULL;
    QLabel *contentsLabel=NULL;
    QLabel *timeLabel=NULL;                  //设置四个标签用以显示不同内容
    QGridLayout *layout = NULL;
signals:

public slots:
};

#endif // SESSIONLISTITEMOFMAIN_H
