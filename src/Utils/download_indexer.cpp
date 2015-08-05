#include "download_indexer.h"

#include "constantes.h"

DownloadIndexer::DownloadIndexer(QWidget *parent) : QWidget(parent)
{
    mainDir = QDir(DOWNLOAD_PATH);
    filePathList = scanDir(mainDir);
    saveIndex(filePathList);

    exit(0);
}

DownloadIndexer::~DownloadIndexer()
{

}

QList<QString> DownloadIndexer::scanDir(QDir dir)
{
    QList<QString> list;
    QList<QString> listBuffer;

    dir.setNameFilters( QStringList() << "*.jpg" << "*.png" << "*.gif" << ".webm" );
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    qDebug() << "Scanning: " << dir.path();

    QFileInfoList fileList = dir.entryInfoList();
    for (int i=0; i<fileList.count(); i++)
    {
        qDebug() << "Found file: " << fileList.at(i).absoluteFilePath();
        list.push_back(fileList.at(i).absoluteFilePath());
    }

    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QStringList dirList = dir.entryList();
    for (int i=0; i<dirList.size(); ++i)
    {
        QString newPath = QString("%1/%2").arg(dir.absolutePath()).arg(dirList.at(i));
        listBuffer = scanDir(QDir(newPath));

        for(int i=0;i<listBuffer.size();i++)
        {
            list.push_back(listBuffer.at(i));
        }
    }

    return list;
}

void DownloadIndexer::saveIndex(QList<QString> list)
{
    std::string filePath = std::string(CONF_PATH) + "file_list.json";

    Json::Value root;
    Json::StyledWriter writer;

    std::string buffer;

    //E:/My Programs/Builds/FuChan/downloads/w/Hatsune Miku/1433970162007.jpg

    for(int i=0; i<list.size();i++)
    {
        //buffer = list.at(i).toStdString().substr(list.at(i).toStdString().find_last_of(DOWNLOAD_PATH)+2,list.at(i).toStdString().find_first_of("/",list.at(i).toStdString().find_last_of(DOWNLOAD_PATH)));
        //root["files"][i]["board"] = buffer;

        buffer = list.at(i).toStdString().substr(list.at(i).toStdString().find_last_of("/")+1,list.at(i).toStdString().size());
        root["files"][i]["name"] = buffer;

        root["files"][i]["path"] = list.at(i).toStdString();
    }

    saveJSONFile(filePath.c_str(), writer.write(root));
}
