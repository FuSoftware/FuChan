#include "caching_worker.h"

// --- CONSTRUCTOR ---
CachingWorker::CachingWorker(const char* url, char outfilename[4096], bool needs_output, bool check)
{
    file_url = strdup(url);
    output_text = needs_output;
    check_file = check;
    strncpy(file_name, outfilename, 4096);
    OP_index = -1;
}

CachingWorker::CachingWorker(const char* url, char outfilename[4096], bool needs_output, bool check, int index)
{
    file_url = strdup(url);
    output_text = needs_output;
    check_file = check;
    strncpy(file_name, outfilename, 4096);
    OP_index = index;
}

CachingWorker::CachingWorker()
{

}

// --- DECONSTRUCTOR ---
CachingWorker::~CachingWorker()
{
    // free resources
}

// --- PROCESS ---
void CachingWorker::process()
{
    connection_state = cachingFile(file_url,file_name,output_text, check_file);
    if(OP_index == -1)
    {
        emit finished();
    }
    else
    {
        emit finished(OP_index);
    }
}

