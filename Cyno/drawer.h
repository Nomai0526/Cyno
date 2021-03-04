#ifndef DRAWER_H
#define DRAWER_H

#include <QToolBox>
#include <QToolButton>
#include "widget.h"

class Drawer : public QToolBox
{
    Q_OBJECT
public:
    explicit Drawer(QWidget *parent = 0);

signals:

public slots:
    void showMyWidget();
private:
    QToolButton *btn1;
    QToolButton *btn2;
    QToolButton *btn3;
    QToolButton *btn4;
    Widget *w;

};

#endif // DRAWER_H
