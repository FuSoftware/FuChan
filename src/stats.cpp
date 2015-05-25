#include "stats.h"

void checkStatFile()
{

    std::ifstream ifile(BOARD_LIST_PATH);
    if(!ifile)
    {
        std::ofstream oFile;
        oFile.open(BOARD_LIST_PATH);
        oFile << "{}";
        oFile.close();
    }
}

void increaseSearchCount()
{
    checkStatFile();
    Json::StyledWriter writer;
    Json::Value root = loadJSONFile(STATS_FILE);

    if(root["search_count"].isInt())
    {
        root["search_count"] = root["search_count"].asInt() + 1;
    }
    else
    {
        root["search_count"] = 1;
    }

    saveJSONFile(STATS_FILE,writer.write(root));
}

void increaseViewedPicture()
{
    checkStatFile();
    Json::StyledWriter writer;
    Json::Value root = loadJSONFile(STATS_FILE);

    if(root["viewed_count"].isInt())
    {
        root["viewed_count"] = root["viewed_count"].asInt() + 1;
    }
    else
    {
        root["viewed_count"] = 1;
    }

    saveJSONFile(STATS_FILE,writer.write(root));
}

void increaseDownloadedPicture()
{
    checkStatFile();
    Json::StyledWriter writer;
    Json::Value root = loadJSONFile(STATS_FILE);

    if(root["download_count"].isInt())
    {
        root["download_count"] = root["download_count"].asInt() + 1;
    }
    else
    {
        root["download_count"] = 1;
    }

    saveJSONFile(STATS_FILE,writer.write(root));
}

void increasePostsLoaded()
{
    checkStatFile();
    Json::StyledWriter writer;
    Json::Value root = loadJSONFile(STATS_FILE);

    if(root["post_count"].isInt())
    {
        root["post_count"] = root["post_count"].asLargestUInt() + 1;
    }
    else
    {
        root["post_count"] = 1;
    }

    saveJSONFile(STATS_FILE,writer.write(root));
}

void increaseThumbLoaded()
{
    checkStatFile();
    Json::StyledWriter writer;
    Json::Value root = loadJSONFile(STATS_FILE);

    if(root["thumb_count"].isInt())
    {
        root["thumb_count"] = root["thumb_count"].asLargestUInt() + 1;
    }
    else
    {
        root["thumb_count"] = 1;
    }

    saveJSONFile(STATS_FILE,writer.write(root));
}

void increaseThreadLoaded()
{
    checkStatFile();
    Json::StyledWriter writer;
    Json::Value root = loadJSONFile(STATS_FILE);

    if(root["thread_count"].isInt())
    {
        root["thread_count"] = root["thread_count"].asInt() + 1;
    }
    else
    {
        root["thread_count"] = 1;
    }

    saveJSONFile(STATS_FILE,writer.write(root));
}

void increaseBoardView(std::string board)
{

}

