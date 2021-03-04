#include "192.168.33.141widget.h"

192.168.33.141Widget::192.168.33.141Widget(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    IPEdit = new QLineEdit(this);
    next = new QPushButton(this);
    layout->addWidget(IPEdit,0,0,1,1);
    layout->addWidget(next,1,0,1,1);
    this->setLayout(layout);
    next->setText("确定");
    connect(next,SIGNAL(clicked(bool)),this,SLOT(getIP()));
}
void 192.168.33.141Widget::getIP()
{
    192.168.33.141 = IPEdit->text();
    this->close();
    loginWidget l1;
    l1.show();
}
