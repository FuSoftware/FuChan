#include "board_select_widget.h"


BoardSelectWidget::BoardSelectWidget(QWidget *parent) : QWidget(parent)
{
    mapper = new QSignalMapper(this);
    setParent(parent);
    
    mainLayout = new QVBoxLayout;
    layoutBoard = new QHBoxLayout;
    
    label_board = new QLabel("Board",this);
    line_edit_board = new QLineEdit(this);
    comboBoxPage = new QComboBox(this);

    for(int i=0;i<10;i++)
    {
        comboBoxPage->addItem(QString::number(i+1));
    }

    comboBoxPage->setEditable(true);

    layoutBoard->addWidget(label_board);
    layoutBoard->addWidget(line_edit_board);
    layoutBoard->addWidget(comboBoxPage);

    layoutManualThread = new QHBoxLayout;
    labelThread = new QLabel("(Optional) Enter a thread to load",this);
    lineEditThread = new QLineEdit(this);

    layoutManualThread->addWidget(labelThread);
    layoutManualThread->addWidget(lineEditThread);

    searchLayout = new QVBoxLayout;
    searchLayout->addLayout(layoutBoard);
    searchLayout->addLayout(layoutManualThread);

    layoutProgress = new QVBoxLayout;
    progressBar = new QProgressBar(this);
    progresslabel = new QLabel("Search a board",this);
    layoutProgress->addWidget(progressBar);
    layoutProgress->addWidget(progresslabel);

    progresslabel->setMaximumHeight(24);
    progressBar->setMaximumHeight(24);

    layoutTop = new QHBoxLayout;
    layoutTop->addLayout(searchLayout);
    layoutTop->addLayout(layoutProgress);
    
    w = new QWidget(this);
    layoutThreads = new QGridLayout;
    
    w->setLayout(layoutThreads);

    /*Initialisation PostWidgets*/
    for(int i = 0;i<15;i++)
    {
        label_thread_no[i] = new QPushButton("Waiting", this);
        label_thumbnail[i] = new QLabel(this);
        label_thread_subject[i]= new QTextBrowser(this);
        label_thread_subject[i]->setText("");

        layoutThread[i] = new QHBoxLayout;

        layoutThread[i]->addWidget(label_thread_no[i]);

        QPixmap pixmap = QPixmap(LOADING_LOGO_PATH);
        label_thumbnail[i]->setPixmap(pixmap.scaled(90,90, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        layoutThread[i]->addWidget(label_thumbnail[i]);

        layoutThread[i]->addWidget(label_thread_subject[i]);

        if(i == 0)
        {
            layoutThreads->addLayout(layoutThread[i],0,0,1,2);
        }
        else if(i < 8)
        {
            layoutThreads->addLayout(layoutThread[i],i,0);
        }
        else
        {
            layoutThreads->addLayout(layoutThread[i],i-7,1);
        }
    }

    /*Assignation des layouts sur le layout principal*/
    mainLayout->addLayout(layoutTop);
    mainLayout->addWidget(w);
    
    setLayout(mainLayout);

    connect(line_edit_board,SIGNAL(returnPressed()),this,SLOT(startLoadingOPs()));
    connect(lineEditThread,SIGNAL(returnPressed()),this,SLOT(thread_load_toggled()));
    connect(comboBoxPage,SIGNAL(currentIndexChanged(int)),this,SLOT(startLoadingOPs(int)));
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(thread_load_toggled(int)));
}

BoardSelectWidget::~BoardSelectWidget()
{

}

void BoardSelectWidget::thread_load_toggled()
{
    emit load_query();
}

void BoardSelectWidget::thread_load_toggled(int i)
{
    emit load_query(i);
}

std::string BoardSelectWidget::getBoard()
{
    return line_edit_board->text().toStdString();
}

int BoardSelectWidget::getThread()
{
    return lineEditThread->text().toInt();
}

int BoardSelectWidget::getThreadIDFromIndex(int index)
{
    return label_thread_no[index]->text().toInt();
}

void BoardSelectWidget::startLoadingOPs(int i)
{
    startLoadingOPs();
}

void BoardSelectWidget::startLoadingOPs()
{
    progresslabel->setText(QString("Downloading board index"));
    board = line_edit_board->text().toStdString();
    page = comboBoxPage->currentText().toInt();

    //http://a.4cdn.org/board/pagenumber.json
    url = std::string(APIURL) + board + std::string("/") + intToString(page) + std::string(".json");
    outfilename = std::string(CACHE_PATH) + board + std::string("/posts/") + std::string("search") + std::string(".json");

    checkFolder(std::string(CACHE_PATH) + board + std::string("/posts/"));

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

void BoardSelectWidget::startDownloadThumbnails()
{
    /*Deleting qThread*/
    //qThread->quit();
    //delete qThread;

    /*Updating loading bar*/
    progresslabel->setText(QString("Loading OPs"));

    /*Reseting widget*/
    delete w;
    layoutThreads = new QGridLayout;
    w = new QWidget(this);
    w->setLayout(layoutThreads);
    mainLayout->addWidget(w);

    Json::Value root = loadJSONFile(outfilename.c_str());

    post_number = 0;
    loaded_posts = 0;
    while(root["threads"][post_number]["posts"][0] != Json::nullValue)
    {
        post_number++;
    }

    for(int i=0;i<MAX_OP_NUMBER;i++)
    {
        thread_op[i] = new Post(root["threads"][i]["posts"][0],board);

        thumb_thread[i] = new QThread(this);
        thumb_worker[i] = new CachingWorker(thread_op[i]->getAttachement().getThumbUrl().c_str(),strdup(thread_op[i]->getAttachement().getThumbPath().c_str()),true,false,i);

        thumb_worker[i]->moveToThread(thumb_thread[i]);

        connect(thumb_thread[i], SIGNAL(started()), thumb_worker[i], SLOT(process()));
        connect(thumb_worker[i], SIGNAL(finished()), thumb_thread[i], SLOT(quit()));
        connect(thumb_worker[i], SIGNAL(finished()), thumb_worker[i], SLOT(deleteLater()));
        connect(thumb_worker[i], SIGNAL(finished(int)), this, SLOT(loadOP(int)));
        connect(thumb_thread[i], SIGNAL(finished()), thumb_thread[i], SLOT(deleteLater()));

        thumb_thread[i]->start();
    }
}

void BoardSelectWidget::loadOP(int index)
{
    /*Stopping QThread*/
    //thumb_thread[index]->quit();

    /*Delete loading QThread and Worker*/
    //delete thumb_thread[index];
    //delete thumb_worker[index];

    /*Deleting previous objects*/
    /*
    delete label_thread_no[index];
    delete label_thumbnail[index];
    delete label_thread_subject[index];
    delete layoutThread[index];
    */

    /*Loading new objects*/
    layoutThread[index] = new QHBoxLayout;

    label_thread_no[index] = new QPushButton(ULintToString(thread_op[index]->getNo()).c_str(), this);
    label_thumbnail[index] = new QLabel(this);
    label_thread_subject[index]= new QTextBrowser(this);
    label_thread_subject[index]->setText(thread_op[index]->getCom().c_str());

    layoutThread[index]->addWidget(label_thread_no[index]);

    /*Loading OP's thumbnail*/
    if(thread_op[index]->hasAttachement())
    {
        QPixmap pixmap = QPixmap(thread_op[index]->getAttachement().getThumbPath().c_str());
        label_thumbnail[index]->setPixmap(pixmap.scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        layoutThread[index]->addWidget(label_thumbnail[index]);
    }

    layoutThread[index]->addWidget(label_thread_subject[index]);

    /*Setting up layout type*/
    if(index == 0)
    {
        layoutThreads->addLayout(layoutThread[index],0,0,1,2);
    }
    else if(index < 8)
    {
        layoutThreads->addLayout(layoutThread[index],index,0);
    }
    else
    {
        layoutThreads->addLayout(layoutThread[index],index-7,1);
    }

    /*Linking to mapper*/
    mapper->setMapping(label_thread_no[index], index);
    connect(label_thread_no[index], SIGNAL(clicked()), mapper , SLOT(map()));

    loaded_posts++;

    /*Progress Update*/
    progressBar->setValue(((loaded_posts+1)*100)/post_number);
    progresslabel->setText(QString("Loaded OP ") + QString::number(loaded_posts) + QString("/") + QString::number(post_number));

    /*Deleting Post* var*/
    delete thread_op[index];
}
