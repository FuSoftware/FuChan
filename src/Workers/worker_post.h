#ifndef WORKERPOST_H
#define WORKERPOST_H

#include <QObject>
#include "Widget/post_widget.h"

class WorkerPost : public QObject
{
    Q_OBJECT
public:
    WorkerPost(PostWidget* post);
    ~WorkerPost();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);

private:
    PostWidget* parent_post;
};

#endif // WORKERPOST_H
