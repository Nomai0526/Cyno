
#include <QVBoxLayout>
#include <QLabel>

class IMToolItem : public QWidget {
    Q_OBJECT
public:
    IMToolItem(const QString &title,
             QWidget *parent = 0) : QWidget(parent), layout(new QVBoxLayout)
    {
        layout = new QVBoxLayout;
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(new QLabel(title));
        setLayout(layout);

        layout->setContentsMargins(0,0,0,0);
        layout->setSpacing(0);
    }

    void addItem(QWidget *item)
    {
        m_itemList.append(item);
        layout->addWidget(item);
        item->setVisible(false);
    }

protected:
    void mousePressEvent(QMouseEvent *event)
    {
        for (int i=0; i<m_itemList.size(); ++i)
        {
            m_itemList[i]->setVisible(!m_itemList[i]->isVisible());
        }
    }

private:
    QList<QWidget *> m_itemList;
    QVBoxLayout *layout;
};

class IMToolBox : public QWidget {
    Q_OBJECT
public:

    IMToolBox(QWidget *parent = 0) : QWidget(parent), layout(new QVBoxLayout)
    {
        setLayout(layout);
        layout->setContentsMargins(0,0,0,0);
        layout->setSpacing(0);
    }

    void addItem(IMToolItem *item)
    {
        layout->addWidget(item);
    }

private:
    QVBoxLayout *layout;
};
