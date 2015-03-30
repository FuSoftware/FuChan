#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include "Widget/thread_widget.h"

class WorkerThread : public QObject
{
    Q_OBJECT
public:
    WorkerThread(ThreadWidget* thread, int index);
    ~WorkerThread();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);

private:
    ThreadWidget* parent_thread;
    int post_index;
};

#endif // WORKERTHREAD_H
