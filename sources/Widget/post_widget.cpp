#include "post_widget.h"

#define THUMB_MAX_SIZE 200

PostWidget::PostWidget(Post *post, QWidget *parent)
{
    setParent(parent);
    post_data = post;
    QVBoxLayout *layoutMain = new QVBoxLayout;
    gridLayout = new QGridLayout;

    subject = new QLabel(this);
    comment = new QTextBrowser(this);
    thumb = new ClickableLabel("",0);

    /*Layouts*/
    /*If OP*/
    if(post_data->isOP)
    {
        gridLayout->addWidget(thumb,1,0,2,2);
        gridLayout->addWidget(subject,0,0,2,1);
        gridLayout->addWidget(comment,1,2);
    }
    /**/
    else if(post_data->has_attachement)
    {
        gridLayout->addWidget(thumb,0,0,2,2);
        gridLayout->addWidget(comment,0,2);
    }
    else
    {
        gridLayout->addWidget(comment,0,0);
    }

    layoutMain->addLayout(gridLayout);
    layoutMain->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    comment->setMaximumSize(width() - THUMB_MAX_SIZE,THUMB_MAX_SIZE);

    setLayout(layoutMain);
    load_post();

    comment->updateGeometry();
}

PostWidget::~PostWidget()
{
    delete thumb;
}

void PostWidget::load_post()
{
    subject->setText(post_data->sub.c_str());
    comment->setText(post_data->com.c_str());

    if(post_data->has_attachement)
    {
        checkFolder(std::string(CACHE_PATH) + post_data->attachement.board + "/thumbs/");
        qThread = new QThread(this);
        worker = new CachingWorker(post_data->attachement.thumb_url.c_str(),strdup(post_data->attachement.thumb_path.c_str()),true,true);

        worker->moveToThread(qThread);

        connect(qThread, SIGNAL(started()), worker, SLOT(process()));
        connect(worker, SIGNAL(finished()), qThread, SLOT(quit()));
        connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(worker, SIGNAL(finished()), this, SLOT(load_thumbnail()));
        connect(qThread, SIGNAL(finished()), qThread, SLOT(deleteLater()));

        qThread->start();
    }
    else
    {
        comment->setMaximumHeight(100);
    }

    outputInfo("INFO",
               std::string("Post ") + ULintToString(post_data->no) + std::string(" loaded"),
               LEVEL_POST);
}

void PostWidget::load_thumbnail()
{
    QSize imageSize;
    imageSize.setWidth(THUMB_MAX_SIZE);
    imageSize.setHeight(THUMB_MAX_SIZE);
    QPixmap pixmap = QPixmap(post_data->attachement.thumb_path.c_str());
    thumb->setPixmap(pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    comment->setMaximumHeight(thumb->height());

    update();
}

void PostWidget::setCommentBoxPolicy(QSizePolicy::Policy policyH, QSizePolicy::Policy policyV)
{
    comment->setSizePolicy(policyH,policyV);
}
