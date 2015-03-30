#include "posted_file.h"

#include <iostream>

PostedFile::PostedFile()
{

}

PostedFile::~PostedFile()
{

}

void PostedFile::loadFromJSON(Json::Value root, std::string board)
{
    /*Image*/
    tim = root["tim"].asLargestUInt();
    filename = root["filename"].asString();
    ext = root["ext"].asString();
    fsize = root["fsize"].asInt();
    md5 = root["md5"].asString();
    w = root["w"].asInt();
    h = root["h"].asInt();
    tn_w = root["tn_w"].asInt();
    tn_h = root["tn_h"].asInt();
    filedeleted = root["filedeleted"].asBool();
    spoiler = root["spoiler"].asBool();

    thumb_url = std::string(ThumbURL) + board + "/" + int64ToString(tim) + std::string("s.jpg");
    thumb_path = std::string(CACHE_PATH) + board + "/thumbs/" + int64ToString(tim) + std::string("s.jpg");

    file_url = std::string(ImageURL) + board + "/" + int64ToString(tim) + ext;
    file_path_cache = std::string(CACHE_PATH) + board + "/images/" + int64ToString(tim) + ext;
    file_path_download = std::string(DOWNLOAD_PATH) + board + "/" + int64ToString(tim) + ext;

    //checkFolder(std::string(CACHE_PATH) + board + "/thumbs/");
    //cachingFile(thumb_url.c_str(),strdup(thumb_path.c_str()),true,true);
}

