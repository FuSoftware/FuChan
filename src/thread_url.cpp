#include "thread_url.h"

ThreadURL::ThreadURL()
{

}

ThreadURL::ThreadURL(std::string url)
{
    parse_url(url);
}

ThreadURL::~ThreadURL()
{

}

void ThreadURL::parse_url(std::string url)
{
    //https://boards.4chan.org/b/thread/627903546#q627903546
    this->url = url;

    //Get post ID
    if (url.find("#q")!=std::string::npos)
    {
        this->post_id = atoi(url.substr(url.find_last_of("#q")+1,url.length()).c_str());
        url = url.substr(0,url.find_last_of("#q")-1);
    }

    //Get Thread ID
    this->id = atoi(url.substr(url.find_last_of("/")+1,url.length()).c_str());
    url = url.substr(0,url.find_last_of("/"));

    //Get board name
    url = url.substr(0,url.find_last_of("/"));
    this->board = url.substr(url.find_last_of("/")+1,url.length());
}

int ThreadURL::getPostID()
{
    return this->post_id;
}

int ThreadURL::getID()
{
    return this->id;
}

std::string ThreadURL::getBoard()
{
    return this->board;
}

