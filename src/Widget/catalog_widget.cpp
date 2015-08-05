#include "catalog_widget.h"

CatalogWidget::CatalogWidget(QWidget *parent) : QWidget(parent)
{
    mapper = new QSignalMapper(this);

    layoutMain = new QVBoxLayout;
    comboBoxSelectBoard = new QComboBox(this);

    scrollArea = new QScrollArea(this);
    areaWidget = new QWidget(this);
    layoutPosts = new QGridLayout;

    int k=0;

    Json::Value board_root = loadJSONFile(BOARD_LIST_PATH);
    while(board_root["boards"][k].isObject())
    {
        board_labels.push_back(generateBoardLabel(board_root["boards"][k]["board"].asString(), board_root["boards"][k]["title"].asString()));
        board_list.push_back(board_root["boards"][k]["board"].asString());
        comboBoxSelectBoard->addItem(QString(board_labels.at(k).c_str()));
        k++;
    }

    //QList<PostWidget*> post_widgets;

    areaWidget->setLayout(layoutPosts);
    scrollArea->setWidget(areaWidget);
    scrollArea->setWidgetResizable(true);

    layoutMain->addWidget(comboBoxSelectBoard);
    layoutMain->addWidget(scrollArea);

    setLayout(layoutMain);

    connect(comboBoxSelectBoard,SIGNAL(currentTextChanged(QString)),this,SLOT(startLoadingOPs(QString)));
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(thread_load_toggled(int)));
}

CatalogWidget::~CatalogWidget()
{

}

std::string CatalogWidget::generateBoardLabel(std::string board, std::string title)
{
    std::ostringstream oss;
    oss << std::setw(3) << std::setiosflags(std::ios_base::left) << board  << " - " << title;
    return oss.str();
}

std::string CatalogWidget::getBoard()
{
    return board_list.at(comboBoxSelectBoard->currentIndex());
}

void CatalogWidget::startLoadingOPs(QString string)
{
    downloadCatalog();
}

void CatalogWidget::thread_load_toggled(int i)
{
    emit load_query(i);
}

void CatalogWidget::downloadCatalog()
{
    board = getBoard();

    //http://a.4cdn.org/board/catalog.json
    url = std::string(APIURL) + board + std::string("/catalog.json");
    outfilename = std::string(CACHE_PATH) + board + std::string("/catalog.json");

    checkFolder(std::string(CACHE_PATH) + board);

    worker = 0;
    qThread = 0;


    qThread = new QThread(this);
    worker = new CachingWorker(url.c_str(),strdup(outfilename.c_str()),true,false);

    worker->moveToThread(qThread);

    connect(qThread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), qThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), this, SLOT(startDownloadThumbnails()));
    connect(qThread, SIGNAL(finished()), qThread, SLOT(deleteLater()));

    qThread->start();
}

void CatalogWidget::startDownloadThumbnails()
{
    /*Reseting widget*/
    if(!catalog_op_widgets.empty())
    {
        for(int i=0;i<catalog_op_widgets.size();i++)
        {
            delete catalog_op_widgets.at(i);
        }
        catalog_op_widgets.clear();
    }


    if(!thread_ops.empty())
    {
        for(unsigned int i=0;i<thread_ops.size();i++)
        {
            delete thread_ops.at(i);
        }
        thread_ops.clear();
    }

    catalog_op_ids.clear();

    Json::Value root = loadJSONFile(outfilename.c_str());

    page_number = 0;
    post_number = 0;

    post_total = 0;

    loaded_posts = 0;
    while(root[page_number].isObject())
    {
        while(root[page_number]["threads"][post_number].isObject())
        {
            post_number++;

            thread_ops.push_back(new Post(root[page_number]["threads"][post_number],board));

            post_total++;
        }
        page_number++;
        post_number = 0;
    }

    for(unsigned int i=0;i<thread_ops.size();i++)
    {
        thumb_threads.push_back(new QThread(this));
        thumb_workers.push_back(new CachingWorker(thread_ops.at(i)->getAttachement().getThumbUrl().c_str(),strdup(thread_ops.at(i)->getAttachement().getThumbPath().c_str()),false,false,i));

        thumb_workers.at(i)->moveToThread(thumb_threads.at(i));

        connect(thumb_threads.at(i), SIGNAL(started()), thumb_workers.at(i), SLOT(process()));
        connect(thumb_workers.at(i), SIGNAL(finished()), thumb_threads.at(i), SLOT(quit()));
        connect(thumb_workers.at(i), SIGNAL(finished()), thumb_workers.at(i), SLOT(deleteLater()));
        connect(thumb_workers.at(i), SIGNAL(finished(int)), this, SLOT(loadOP(int)));
        connect(thumb_threads.at(i), SIGNAL(finished()), thumb_threads.at(i), SLOT(deleteLater()));

        thumb_threads.at(i)->start();
    }
}

void CatalogWidget::loadOP(int index)
{
    /*Loading new objects*/
    catalog_op_widgets.push_back(new CatalogOpWidget(thread_ops.at(index),this));
    catalog_op_ids.push_back(index);

    int current_index = catalog_op_widgets.size()-1;

    layoutPosts->addWidget(catalog_op_widgets.at(current_index),index/7,index%7);


    /*Linking to mapper*/
    mapper->setMapping(catalog_op_widgets.at(current_index), index);
    connect(catalog_op_widgets.at(current_index), SIGNAL(thumb_clicked()), mapper , SLOT(map()));

    scrollArea->update();
    scrollArea->show();
}

