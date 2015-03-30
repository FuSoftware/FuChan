#include "worker_post.h"

// --- CONSTRUCTOR ---
WorkerPost::WorkerPost(PostWidget *post)
{
    parent_post = post;
}

// --- DECONSTRUCTOR ---
WorkerPost::~WorkerPost()
{

}

// --- PROCESS ---
void WorkerPost::process()
{
    emit finished();
}


