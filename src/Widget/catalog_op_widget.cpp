#include "catalog_op_widget.h"

CatalogOpWidget::CatalogOpWidget(Post *thread_op, QWidget *parent) : QWidget(parent)
{
    layoutMain = new QVBoxLayout;

    thumbnail = new ClickableLabel("",0);
    title = new QLabel(this);

    secondaryLayout = new QHBoxLayout;
    replies = new QLabel(this);
    images = new QLabel(this);

    comment = new QTextBrowser(this);

    QPixmap pixmap = QPixmap(thread_op->getAttachement().getThumbPath().c_str());
    thumbnail->setPixmap(pixmap.scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    title->setText(thread_op->getSubject().c_str());
    replies->setText(QString("Reps : ") + QString::number(thread_op->getReplies()));
    images->setText(QString("Pics : ") + QString::number(thread_op->getImages()));

    comment->setText(thread_op->getCom().c_str());

    secondaryLayout->addWidget(replies);
    secondaryLayout->addWidget(images);

    layoutMain->addWidget(thumbnail);
    layoutMain->addWidget(title);
    layoutMain->addLayout(secondaryLayout);
    layoutMain->addWidget(comment);

    setLayout(layoutMain);

    connect(thumbnail,SIGNAL(clicked()),this,SLOT(emit_thumb_clicked()));
}

CatalogOpWidget::~CatalogOpWidget()
{

}

void CatalogOpWidget::emit_thumb_clicked()
{
    emit thumb_clicked();
}
