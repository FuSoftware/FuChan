#ifndef THREADWIDGET_H
#define THREADWIDGET_H

#include <QWidget>
#include <thread.h>
#include "post_widget.h"
#include "widget.h"
#include "../Workers/thread_dumping_worker.h"

class Widget;

class ThreadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThreadWidget(std::string board, int thread_number, bool favourite, bool pics_only, Widget *parent = 0);
    ~ThreadWidget();
    void load();

    Thread *getThread();

    QSignalMapper *mapper;
    std::string thread_board;
    int thread_id;

    Widget* parent_widget;

    Thread *thread;
    QPushButton *push_button_update;
    QPushButton *push_button_dump_thread;
    QPushButton *push_button_favourite;

    PostWidget *posts[MAX_POST_NUMBER];
    QScrollArea *scrollArea;
    QWidget *areaWidget;
    QVBoxLayout *mainLayout;
    QGridLayout *secondaryLayout;

    QThread *qThread;
    ThreadDumpingWorker *worker;

signals:

public slots:
   void reload();
   void setViewer(int sender);
   void toggleFavourite(bool state);
   void dump_thread();
   void download_finished(int downloaded, int count);

private:
   int download_started;
   int download_finished_count;
   bool pics_only;

};

#endif // THREADWIDGET_H
