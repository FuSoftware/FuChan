#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include "json/json.h"
#include "constantes.h"
#include "post.h"

class Thread
{
public:
    Thread(std::string board, int thread_number);
    Thread();
    ~Thread();
    void load(std::string board, int thread_number);
    int getPostCount();
    Post *getPost(int i);

private:
    Json::Value posts_json[MAX_POST_NUMBER];
    Post *posts[MAX_POST_NUMBER];
    int posts_id[MAX_POST_NUMBER];

    std::string board_id;
    std::string subject;
    int thread_id;
    int post_count;

    bool favourited;
};

#endif // THREAD_H
