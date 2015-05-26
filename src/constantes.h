#ifndef CONSTANTES
#define CONSTANTES

#define DEBUG 0

#define APP_VERSION "0.17.0.3"
#define APP_NAME "FuChan"


#if DEBUG
    #if _WIN32
        #define CACHE_PATH "E:/My Programs/Builds/FuChan/cache/"
        #define DOWNLOAD_PATH "E:/My Programs/Builds/FuChan/downloads/"
        #define CONF_PATH "E:/My Programs/Builds/FuChan/conf/"
        #define LOADING_LOGO_PATH "E:/My Programs/Builds/FuChan/conf/logo.png"
        #define FAVORITE_THREADS_PATH "E:/My Programs/Builds/FuChan/conf/favourites.json"
        #define BOARD_LIST_PATH "E:/My Programs/Builds/FuChan/conf/boards.json"
        #define STATS_FILE "E:/My Programs/Builds/FuChan/conf/stats.json"
    #elif __linux
        #define CACHE_PATH "/usr/share/FuChan/cache/"
        #define DOWNLOAD_PATH "/usr/share/FuChan/downloads/"
        #define CONF_PATH "/usr/share/FuChan/conf/"
        #define LOADING_LOGO_PATH "/usr/share/FuChan/conf/logo.png"
        #define FAVORITE_THREADS_PATH "/usr/share/FuChan/conf/favourites.json"
        #define BOARD_LIST_PATH "/usr/share/FuChan/conf/boards.json"
        #define STATS_FILE "/usr/share/FuChan/conf/stats.json"
    #endif
#else
    #define CACHE_PATH "cache/"
    #define DOWNLOAD_PATH "downloads/"
    #define CONF_PATH "conf/"
    #define LOADING_LOGO_PATH "conf/logo.png"
    #define FAVORITE_THREADS_PATH "conf/favourites.json"
    #define BOARD_LIST_PATH "conf/boards.json"
    #define STATS_FILE "conf/stats.json"
#endif

#define MAX_POST_NUMBER 512
#define MAX_OP_NUMBER 15
#define APIURL    "https://a.4cdn.org/"
#define ImageURL  "https://i.4cdn.org/"
#define ThumbURL  "https://t.4cdn.org/"
#define StaticURL "https://s.4cdn.org/"

#define BoardURL  "https://a.4cdn.org/boards.json"

#define SearchTabIndex 0
#define ViewerTabIndex 1
#define OptionTabIndex 2

enum InfoLevel
{
    LEVEL_CACHING = 1,
    LEVEL_POST,
    LEVEL_THREAD,
    LEVEL_TOP_WIDGET
};

#endif // CONSTANTES

