#include "post_widget.h"

#define THUMB_MAX_SIZE 200

PostWidget::PostWidget(Post *post, QWidget *parent)
{
    setParent(parent);
    post_data = post;
    QVBoxLayout *layoutMain = new QVBoxLayout;
    gridLayout = new QGridLayout;

    labelPostNo = new QLabel(this);
    labelSize = new QLabel(this);
    comment = new QTextBrowser(this);
    thumb = new ClickableLabel("",0);

    /*Layouts*/
    if(post_data->hasAttachement())
    {
        //Row, Column, RowSpan, ColSpan
        gridLayout->addWidget(labelPostNo,0,0,1,2);
        gridLayout->addWidget(thumb      ,1,0,3,2);
        gridLayout->addWidget(labelSize  ,4,0,1,2);

        gridLayout->addWidget(comment    ,0,2,5,1);
    }
    else
    {
        gridLayout->addWidget(labelPostNo,0,0,1,1);
        gridLayout->addWidget(comment    ,1,0,3,1);
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
    comment->setText(post_data->getCom().c_str());

    labelPostNo->setText(QString::number(post_data->getNo()));
    labelPostNo->setAlignment(Qt::AlignLeft);
    labelPostNo->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    if(post_data->hasAttachement())
    {
        labelPostNo->setAlignment(Qt::AlignCenter);
        checkFolder(std::string(CACHE_PATH) + post_data->getAttachement().getBoard() + "/thumbs/");
        qThread = new QThread(this);
        worker = new CachingWorker(post_data->getAttachement().getThumbUrl().c_str(),strdup(post_data->getAttachement().getThumbPath().c_str()),true,true);

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
               std::string("Post ") + ULintToString(post_data->getNo()) + std::string(" loaded"),
               LEVEL_POST);
}

void PostWidget::load_thumbnail()
{
    QSize imageSize;
    imageSize.setWidth(THUMB_MAX_SIZE);
    imageSize.setHeight(THUMB_MAX_SIZE);
    QPixmap pixmap = QPixmap(post_data->getAttachement().getThumbPath().c_str());
    thumb->setPixmap(pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    thumb->setAlignment(Qt::AlignCenter);

    comment->setMaximumHeight(thumb->height());

    labelSize->setText(QString::number(post_data->getAttachement().getWidth()) + QString("x") + QString::number(post_data->getAttachement().getHeight()));
    labelSize->setAlignment(Qt::AlignCenter);


    update();
}

void PostWidget::setCommentBoxPolicy(QSizePolicy::Policy policyH, QSizePolicy::Policy policyV)
{
    comment->setSizePolicy(policyH,policyV);
}
