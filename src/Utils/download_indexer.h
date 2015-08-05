#ifndef DOWNLOADINDEXER_H
#define DOWNLOADINDEXER_H

#include <QtWidgets>

#include <QDir>

#include "../fonctions_json.h"

class DownloadIndexer : public QWidget
{
    Q_OBJECT
public:
    explicit DownloadIndexer(QWidget *parent = 0);
    ~DownloadIndexer();

    QList<QString> scanDir(QDir dir);
    void saveIndex(QList<QString> list);

signals:

public slots:

private:
    QDir mainDir;
    QList<QString> filePathList;
};

#endif // DOWNLOADINDEXER_H
