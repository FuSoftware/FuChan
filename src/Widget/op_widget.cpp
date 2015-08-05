#include "op_widget.h"

OPWidget::OPWidget(Post* thread_op, int index, QWidget *parent) : QWidget(parent)
{
    this->thread_op = thread_op;

    layoutThread = new QHBoxLayout;
    layout_OP_data = new QVBoxLayout;

    label_thread_no = new QPushButton(ULintToString(thread_op->getNo()).c_str(), this);
    label_thumbnail = new QLabel(this);
    label_title = new QLabel(this);
    label_title->setStyleSheet("QLabel { color : blue; }");
    label_thread_subject = new QTextBrowser(this);
    label_thread_subject->setText(thread_op->getCom().c_str());

    if(!thread_op->getSubject().empty())
    {
        label_title->setText(thread_op->getSubject().c_str());
        layout_OP_data->addWidget(label_title,1);
        layout_OP_data->addWidget(label_thread_subject,2);
    }
    else
    {
        layout_OP_data->addWidget(label_thread_subject);
    }


    layoutThread->addWidget(label_thread_no);

    /*Loading OP's thumbnail*/
    if(thread_op->hasAttachement())
    {
        QPixmap pixmap = QPixmap(thread_op->getAttachement().getThumbPath().c_str());
        label_thumbnail->setPixmap(pixmap.scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        layoutThread->addWidget(label_thumbnail);
    }

    layoutThread->addLayout(layout_OP_data);

    setLayout(layoutThread);

    connect(label_thread_no,SIGNAL(clicked()),this,SLOT(emit_click()));
}

OPWidget::~OPWidget()
{

}

int OPWidget::getID()
{
    return label_thread_no->text().toInt();
}

void OPWidget::emit_click()
{
    emit clicked();
}

