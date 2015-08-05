#ifndef THREADURL_H
#define THREADURL_H

#include <iostream>


class ThreadURL
{
public:
    ThreadURL();
    ThreadURL(std::string url);
    ~ThreadURL();

    void parse_url(std::string url);
    int getPostID();
    int getID();
    std::string getBoard();

private:
    std::string url;
    std::string board;
    int id;
    int post_id;

};

#endif // THREADURL_H
