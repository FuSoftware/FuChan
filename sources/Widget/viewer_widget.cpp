#include "viewer_widget.h"

#include <cstdint>
#include "fonctions.h"

ViewerWidget::ViewerWidget(QWidget *parent) : QWidget(parent)
{
    setParent(parent);

    mainlayout = new QHBoxLayout;
    secondaryLayout = new QVBoxLayout;

    labelImage = new QLabel("Search a picture first",this);
    labelImage->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    labelImage->setMinimumSize(700,700);

    groupBoxInfo = new QGroupBox("Info");
    layoutGroupBox = new QVBoxLayout;
    for(int i=0;i<5;i++)
    {
        labelInfo[i] = new QLabel(this);
        layoutGroupBox->addWidget(labelInfo[i]);
    }
    download_button = new QPushButton("Download",this);
    layoutGroupBox->addWidget(download_button);
    groupBoxInfo->setLayout(layoutGroupBox);

    secondaryLayout->addWidget(groupBoxInfo);
    secondaryLayout->addSpacerItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    mainlayout->addWidget(labelImage);
    mainlayout->addLayout(secondaryLayout);

    setLayout(mainlayout);

    connect(download_button,SIGNAL(clicked()),this,SLOT(download_picture_persistent()));

    image_loaded = false;
}

ViewerWidget::~ViewerWidget()
{

}

void ViewerWidget::load_picture(Post* post)
{
    local_post = post;
    download_picture(local_post, false);

    QSize imageSize;
    imageSize.setWidth(post->attachement.w);
    imageSize.setHeight(post->attachement.h);

    imageSize.setHeight(height());
    imageSize.setWidth(width()-groupBoxInfo->width());


    QPixmap pixmap = QPixmap(QString(post->attachement.file_path_cache.c_str()));
    labelImage->setPixmap(pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    labelInfo[0]->setText(QString("File name : ") + QString(post->attachement.filename.c_str()) +  QString(post->attachement.ext.c_str()));
    labelInfo[1]->setText(QString("File url  : ") + QString(post->attachement.file_url.c_str()));
    labelInfo[2]->setText(QString("File tim  : ") + QString(int64ToString(post->attachement.tim).c_str()));
    labelInfo[3]->setText(QString("File size : ") + QString::number(post->attachement.fsize));;
    labelInfo[4]->setText(QString("Size      : ") + QString::number(post->attachement.w) + QString("x") + QString::number(post->attachement.h));
}

void ViewerWidget::download_picture(Post *post, bool download)
{
    if(download)
    {
        std::string folder = std::string(DOWNLOAD_PATH) + post->parent_board;
        checkFolder(folder);
        cachingFile(post->attachement.file_url.c_str(),strdup(post->attachement.file_path_download.c_str()),true,true);
    }
    else
    {
        std::string folder = std::string(CACHE_PATH) + post->parent_board + std::string("/images/");
        checkFolder(folder);
        cachingFile(post->attachement.file_url.c_str(),strdup(post->attachement.file_path_cache.c_str()),true,true);
    }
}

void ViewerWidget::download_picture_persistent()
{
    download_picture(local_post, true);
}

