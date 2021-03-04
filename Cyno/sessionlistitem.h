#ifndef SESSIONLISTITEM_H
#define SESSIONLISTITEM_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <currentaccount.h>

class sessionListItem : public QWidget
{
    Q_OBJECT
public:
    explicit sessionListItem(QWidget *parent = 0);
    sessionListItem(currentAccount *Account,QString message,QString date,QString time);
    QLabel *avatarLabel=NULL;
    QLabel *nameLabel=NULL;
    QLabel *contentsLabel=NULL;
    QLabel *timeLabel=NULL;                  //设置四个标签用以显示不同内容
    QGridLayout *layout = NULL;
signals:

public slots:
};

#endif // SESSIONLISTITEM_H

//这个是对话列表窗口
