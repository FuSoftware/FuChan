#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "post.h"
#include "clickableLabel.h"
#include "Workers/caching_worker.h"

class PostWidget : public QWidget
{
    Q_OBJECT

public:
    PostWidget(Post *post, QWidget *parent = 0);
    ~PostWidget();
    void load_post();
    void setCommentBoxPolicy(QSizePolicy::Policy policyH, QSizePolicy::Policy policyV);

    ClickableLabel *thumb;

public slots:
    void load_thumbnail();

private:
    QGridLayout *gridLayout;

    QLabel *subject;
    QTextBrowser *comment;

    Post *post_data;

    QThread *qThread;
    CachingWorker *worker;
};

#endif // POSTWIDGET_H
