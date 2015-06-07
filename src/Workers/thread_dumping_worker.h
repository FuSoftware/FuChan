#ifndef THREADDUMPINGWORKER_H
#define THREADDUMPINGWORKER_H

#include <QObject>
#include <QWidget>
#include <QThread>

#include "../post.h"
#include "../thread.h"
#include "caching_worker.h"
#include "../stats.h"

class ThreadDumpingWorker : public QObject
{
    Q_OBJECT
public:
    ThreadDumpingWorker(std::vector<Post*> posts, std::string folder);
    ~ThreadDumpingWorker();

signals:
    void finished();
    void download_status(int, int);

public slots:
    void process();
    void downloadFinished();

private:
    QWidget *parent;

    std::vector<Post *> posts;
    std::vector<QThread *> qThreads;
    std::vector<CachingWorker *> workers;

    int threads_started;
    int download_finished;

    int post_count;
    int to_download;

    std::string folder;
};

#endif // THREADDUMPINGWORKER_H
