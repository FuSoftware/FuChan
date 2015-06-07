#include "thread_dumping_worker.h"

#define PARALLEL_THREADS 5

// --- CONSTRUCTOR ---
ThreadDumpingWorker::ThreadDumpingWorker(std::vector<Post *> posts, std::string folder)
{
    download_finished = 0;
    threads_started = 0;
    to_download = 0;

    this->folder = folder;

    post_count = 0;

    this->posts = posts;

    for(int i=0;i<this->posts.size();i++)
    {
        if(posts.at(i)->hasAttachement())
        {
            post_count++;
        }
    }
}

// --- DECONSTRUCTOR ---
ThreadDumpingWorker::~ThreadDumpingWorker()
{

}

// --- PROCESS ---
void ThreadDumpingWorker::process()
{
    std::string outfilename;
    int j=0;
    int start_limit = 0;

    outputInfo("DEBUG",
               "Total posts : " +intToString(posts.size()),
               LEVEL_TOP_WIDGET);

    outputInfo("DEBUG",
               "With att : " +intToString(post_count),
               LEVEL_TOP_WIDGET);

    for(int i=0;i<posts.size();i++)
    {
        if(posts.at(i)->hasAttachement())
        {
            outfilename = folder + posts.at(i)->getAttachement().getFileNameExt();

            qThreads.push_back(new QThread(this));
            workers.push_back(new CachingWorker(posts.at(i)->getAttachement().getFileUrl().c_str(),strdup(outfilename.c_str()),true,true));

            connect(qThreads.at(j), SIGNAL(started()), workers.at(j), SLOT(process()));
            connect(workers.at(j), SIGNAL(finished()), qThreads.at(j), SLOT(quit()));
            connect(workers.at(j), SIGNAL(finished()), workers.at(j), SLOT(deleteLater()));          
            connect(qThreads.at(j), SIGNAL(finished()),qThreads.at(j), SLOT(deleteLater()));

            connect(workers.at(j), SIGNAL(finished()), this, SLOT(downloadFinished()));

            j++;
        }
    }
    post_count = j;
    start_limit = j;

    if(start_limit > PARALLEL_THREADS)
    {
        start_limit = PARALLEL_THREADS;
    }

    for(int i=0;i<start_limit;i++)
    {
        qThreads.at(i)->start();
        threads_started++;
    }
}

void ThreadDumpingWorker::downloadFinished()
{
    download_finished++;
    increaseDownloadedPicture();

    outputInfo("DEBUG",
                       "Dumped " +intToString(download_finished) + "/" + intToString(post_count),
                       LEVEL_TOP_WIDGET);

    emit download_status(download_finished,post_count);

    if(threads_started < qThreads.size())
    {
        qThreads.at(threads_started)->start();
        threads_started++;
    }
    else if (download_finished == workers.size())
    {
        emit finished();
        outputInfo("DEBUG",
                   "Dumped " +intToString(threads_started) + " pictures",
                   LEVEL_TOP_WIDGET);
    }
    else
    {

    }
}
