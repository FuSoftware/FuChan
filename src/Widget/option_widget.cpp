#include "option_widget.h"

#include "constantes.h"
#include "fileutils.h"
#include "fonctions.h"

OptionWidget::OptionWidget(QWidget *parent) : QWidget(parent)
{
    label_cache_value = new QLabel(this);
    refresh_cache = new QPushButton("Refresh",this);
    delete_cache = new QPushButton("Delete",this);

    layoutCache = new QHBoxLayout;
    layoutCache->addWidget(label_cache_value);
    layoutCache->addWidget(refresh_cache);
    layoutCache->addWidget(delete_cache);
    layoutCache->addSpacerItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    layoutMain = new QVBoxLayout;
    layoutMain->addLayout(layoutCache);
    layoutMain->addSpacerItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(layoutMain);

    refreshCacheSize();

    connect(refresh_cache, SIGNAL(clicked()),this,SLOT(refreshCacheSize()));
    connect(delete_cache,SIGNAL(clicked()),this,SLOT(deleteCache()));
}

OptionWidget::~OptionWidget()
{

}

void OptionWidget::deleteCache()
{
    FileUtils folder;
    bool success;
    success = folder.removeDir(CACHE_PATH);

    if(success)
    {
        refreshCacheSize();
    }
    else
    {
        outputInfo("ERROR",
                   std::string("Error removing cache"),
                   LEVEL_TOP_WIDGET);
    }
}

void OptionWidget::refreshCacheSize()
{
    int cache_size = dir_size(CACHE_PATH);
    QString cache_unit;

    if(cache_size > 1024*1024*1024)
    {
        cache_size = cache_size/(1024*1024*1024);
        cache_unit = " GB";
    }
    if(cache_size > 1024*1024)
    {
        cache_size = cache_size/(1024*1024);
        cache_unit = " MB";
    }
    else if(cache_size > 1024)
    {
        cache_size = cache_size/(1024);
        cache_unit = " kB";
    }
    else
    {
        cache_size = cache_size;
        cache_unit = " B";
    }

    label_cache_value->setText("Cache size : " + QString::number(cache_size) + cache_unit);
}
