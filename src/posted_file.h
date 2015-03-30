#ifndef POSTEDFILE_H
#define POSTEDFILE_H

#include <iostream>
#include <cstdint>
#include "fonctions_json.h"
#include "fonctions.h"
#include "constantes.h"


class PostedFile
{
public:
    PostedFile();
    ~PostedFile();

    void loadFromJSON(Json::Value root, std::string board);

    /*Getters*/
    int64_t getTim();
    int getWidth();
    int getHeight();

    std::string getFileUrl();
    std::string getFilePathCache();
    std::string getFilePathDownload();
    std::string getThumbUrl();
    std::string getThumbPath();
    std::string getBoard();

    /*Setters*/

    /*Image*/
    std::string filename;//Original filename
    std::string ext;//File extension
    int fsize;//File size
    std::string md5;//File MD5
    int tn_w;//Thumb width
    int tn_h;//Thumb height
    bool filedeleted;
    bool spoiler;

private:
    int64_t tim;//Renamed filename	UNIX timestamp + milliseconds
    int w;//Image width
    int h;//Image height

    std::string file_url;
    std::string file_path_cache;
    std::string file_path_download;
    std::string thumb_url;
    std::string thumb_path;
    std::string board;
};

#endif // POSTEDFILE_H
