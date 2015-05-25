#ifndef POST_H
#define POST_H

#include <iostream>
#include "json/json.h"
#include "posted_file.h"

#include "stats.h"

class Post
{
public:
    Post(Json::Value root, std::string board);
    Post();
    ~Post();

    void load(Json::Value root, std::string board);
    void setOP(bool state);

    /*Getters*/
    unsigned long int getNo();
    std::string getCom();
    bool hasAttachement();
    PostedFile getAttachement();
    std::string getParentBoard();

private:
    PostedFile attachement;
    bool has_attachement;
    std::string parent_board;

    /*Post*/
    unsigned long int no;//Post number
    unsigned long int resto;//Reply to
    bool sticky;//Stickied thread?
    bool closed;//Closed thread?
    bool archived;//Archived thread?
    std::string now;//Date and time
    int time;//UNIX timestamp
    std::string name;//Name
    std::string trip;//Tripcode
    std::string ID;//ID
    std::string capcode;//Capcode
    std::string country;//Country code
    std::string country_name;//Country name
    std::string sub;//Subject	text
    std::string com;//Comment	text

    /**/
    unsigned long int custom_spoiler;
    unsigned long int omitted_posts;
    unsigned long int omitted_images;
    unsigned long int replies;
    unsigned long int images;
    bool bumplimit;
    bool imagelimit;
    //capcode_replies
    int last_modified;//Time when last modified	UNIX timestamp
    std::string tag;
    std::string semantic_url;

    bool isOP;
};
/*
capcode_replies	array	Capcode user replies?	array of capcode type and post IDs	{"admin":[1234,1267]}
*/
#endif // POST_H
