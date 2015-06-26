#ifndef OPWIDGET_H
#define OPWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "../post.h"

class OPWidget : public QWidget
{
    Q_OBJECT
public:
    OPWidget(Post *thread_op, int index, QWidget *parent = 0);
    ~OPWidget();

    QPushButton *label_thread_no;
    int getID();

signals:

public slots:

private:
    QHBoxLayout *layoutThread;
    QLabel *label_thumbnail;

    QVBoxLayout *layout_OP_data;
    QLabel *label_title;
    QTextBrowser *label_thread_subject;

    Post *thread_op;
    int index;
};

#endif // OPWIDGET_H
