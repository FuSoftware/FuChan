#ifndef CONSTANTES
#define CONSTANTES

#define DEBUG 0

#define APP_VERSION 0.13
#define APP_NAME "FuChan"


#if DEBUG
    #if _WIN32
        #define CACHE_PATH "E:/FuChan/cache/"
        #define DOWNLOAD_PATH "E:/FuChan/downloads/"
        #define CONF_PATH "E:/FuChan/conf/"
        #define LOADING_LOGO_PATH "E:/FuChan/conf/logo.png"
        #define FAVORITE_THREADS_PATH "E:/FuChan/conf/favourites.json"
    #elif __linux
        #define CACHE_PATH "/usr/share/FuChan/cache/"
        #define DOWNLOAD_PATH "/usr/share/FuChan/downloads/"
        #define CONF_PATH "/usr/share/FuChan/conf/"
        #define LOADING_LOGO_PATH "/usr/share/FuChan/conf/logo.png"
        #define FAVORITE_THREADS_PATH "/usr/share/FuChan/conf/favourites.json"
    #endif
#else
    #define CACHE_PATH "cache/"
    #define DOWNLOAD_PATH "downloads/"
    #define CONF_PATH "conf/"
    #define LOADING_LOGO_PATH "conf/logo.png"
    #define FAVORITE_THREADS_PATH "conf/favourites.json"
#endif

#define MAX_POST_NUMBER 512
#define MAX_OP_NUMBER 15
#define APIURL    "http://a.4cdn.org/"
#define ImageURL  "http://i.4cdn.org/"
#define ThumbURL  "http://t.4cdn.org/"
#define StaticURL "http://s.4cdn.org/"

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

