#include "fonctions.h"
#include "constantes.h"

#include <QFile>
#include <QDir>

void copyFile(std::string source, std::string dest)
{
    std::ifstream  src(source, std::ios::binary);
    std::ofstream  dst(dest,   std::ios::binary);

    dst << src.rdbuf();
}

bool isPair(int number)
{
    if(number & 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void checkFolder(std::string path)
{
    QDir dirCache1(path.c_str());
    if (!dirCache1.exists()) {
        dirCache1.mkpath(".");
    }
}

/*Conversion*/
std::string int64ToString(int64_t i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

std::string ULintToString(unsigned long int i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

std::string intToString(int i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

char* stringToCString(std::string input)
{
    char* output = strdup(input.c_str());
    return output;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d | %X", &tstruct);

    return buf;
}

void outputInfo(std::string type, std::string data, int level)
{
    std::cout << "[" << type << "]"
              << "[" << currentDateTime() << "]"
              << "|";

    for(int i=0;i<level;i++)
    {
        std::cout <<"-";
    }

    std::cout << "> " << data << std::endl;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

/*Read image with cUrl*/
int cachingFile(const char *url, char outfilename[4096], bool output, bool check_file_presence)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    int buf = 0;

    QFile Fout;
    Fout.setFileName(outfilename);
    std::string file = std::string(outfilename);
    std::string folder = file.substr(0,file.find_last_of("/")+1);

    checkFolder(folder);

    if(Fout.exists() && check_file_presence)
    {
        outputInfo("INFO",
                   std::string(std::string("File : ")+std::string(outfilename)+std::string(" exists")),
                   LEVEL_CACHING);
       return 0;
    }
    else
    {
        if(output)
        {
            outputInfo("INFO",
                               std::string(std::string("Caching : ")+std::string(url)),
                               LEVEL_CACHING);
        }

        curl = curl_easy_init();
        if (curl)
        {
            fp = fopen(outfilename,"wb");
            curl_easy_setopt(curl, CURLOPT_INTERFACE, NULL);
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
            curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, buf);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(fp);

            if(buf != 0)
            {
                outputInfo("ERROR",
                           std::string("CUrL error") + intToString(buf),
                           LEVEL_TOP_WIDGET);
            }

            return res;
        }
        else
        {
            outputInfo("ERROR",
                       "CUrL not found",
                       LEVEL_TOP_WIDGET);
            exit(28);
        }
    }

}
