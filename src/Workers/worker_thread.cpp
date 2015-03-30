#include "worker_thread.h"

// --- CONSTRUCTOR ---
WorkerThread::WorkerThread(ThreadWidget* thread, int index)
{
    parent_thread = thread;
    post_index = index;
}

// --- DECONSTRUCTOR ---
WorkerThread::~WorkerThread()
{

}

// --- PROCESS ---
void WorkerThread::process()
{
    parent_thread->posts[post_index] = new PostWidget(parent_thread->thread->getPost(post_index));

    if(post_index == 0)
    {
        parent_thread->secondaryLayout->addWidget(parent_thread->posts[post_index],0,0,1,2);
        parent_thread->posts[post_index]->setCommentBoxPolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    }
    else if(!isPair(post_index))
    {
        parent_thread->secondaryLayout->addWidget(parent_thread->posts[post_index],(post_index+1)/2,0);
    }
    else
    {
        parent_thread->secondaryLayout->addWidget(parent_thread->posts[post_index],post_index/2,1);
    }

    parent_thread->mapper->setMapping(parent_thread->posts[post_index]->thumb, post_index);
    connect(parent_thread->posts[post_index]->thumb, SIGNAL(clicked()), parent_thread->mapper , SLOT(map()));


    emit finished();
}


