#ifndef THREADWIDGET_H
#define THREADWIDGET_H

#include <QWidget>
#include <thread.h>
#include "post_widget.h"
#include "widget.h"

class Widget;

class ThreadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThreadWidget(std::string board, int thread_number, bool favourite, Widget *parent = 0);
    ~ThreadWidget();
    void load();

    QSignalMapper *mapper;
    std::string thread_board;
    int thread_id;

    Widget* parent_widget;

    Thread *thread;
    QPushButton *push_button_update;
    QPushButton *push_button_favourite;

    PostWidget *posts[MAX_POST_NUMBER];
    QScrollArea *scrollArea;
    QWidget *areaWidget;
    QVBoxLayout *mainLayout;
    QGridLayout *secondaryLayout;

signals:

public slots:
   void reload();
   void setViewer(int sender);
   void toggleFavourite(bool state);

private:

};

#endif // THREADWIDGET_H
