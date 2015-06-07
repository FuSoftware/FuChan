#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <vector>
#include "json/json.h"
#include "constantes.h"
#include "post.h"

#include "stats.h"

class Thread
{
public:
    Thread(std::string board, int thread_number);
    Thread();
    ~Thread();
    void load(std::string board, int thread_number);
    int getPostCount();
    Post *getPost(int i);
    std::vector<Post*> getPostList();

private:
    std::vector<Json::Value> posts_json;
    std::vector<Post*> post_list;
    std::vector<int> posts_ids;

    std::string board_id;
    std::string subject;
    int thread_id;
    int post_count;

    bool favourited;
};

#endif // THREAD_H
