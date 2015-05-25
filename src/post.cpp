#include "post.h"

Post::Post(Json::Value root, std::string board)
{
    load(root, board);
}

Post::Post()
{

}

Post::~Post()
{

}

void Post::load(Json::Value root, std::string board)
{

    parent_board = board;
    /*Post*/
    no = root["no"].asLargestUInt();
    resto = root["resto"].asLargestUInt();
    sticky = root["sticky"].asBool();
    closed = root["closed"].asBool();
    archived = root["archived"].asBool();
    now = root["now"].asString();
    time = root["time"].asInt();
    name = root["name"].asString();
    trip = root["trip"].asString();
    ID = root["ID"].asString();
    capcode = root["capcode"].asString();
    country = root["country"].asString();
    country_name = root["country_name"].asString();
    sub = root["sub"].asString();
    com = root["com"].asString();

    /**/
    custom_spoiler = root["custom_spoiler"].asLargestUInt();
    omitted_posts = root["omitted_posts"].asLargestUInt();
    omitted_images = root["omitted_images"].asLargestUInt();
    replies = root["replies"].asLargestUInt();
    images = root["images"].asLargestUInt();
    bumplimit = root["bumplimit"].asBool();
    imagelimit = root["imagelimit"].asBool();
    //capcode_replies
    last_modified = root["last_modified"].asInt();
    tag = root["tag"].asString();
    semantic_url = root["semantic_url"].asString();

    isOP = !sub.empty();

    if(root["tim"].asLargestUInt() != 0)
    {
        attachement.loadFromJSON(root,board);
        has_attachement = true;
    }
    else
    {
        has_attachement = false;
    }

    increasePostsLoaded();
}

/*----------*/
/*Getters*/

unsigned long int Post::getNo()
{
    return no;
}

std::string Post::getCom()
{
    return com;
}

bool Post::hasAttachement()
{
    return has_attachement;
}

PostedFile Post::getAttachement()
{
    return attachement;
}

std::string Post::getParentBoard()
{
    return parent_board;
}


/*----------*/
/*Setters*/

void Post::setOP(bool state)
{
    isOP = state;
}

