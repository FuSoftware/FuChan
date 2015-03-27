#ifndef CACHINGWORKER_H
#define CACHINGWORKER_H

#include <QObject>
#include <QString>
#include "../fonctions.h"

class CachingWorker : public QObject
{
    Q_OBJECT

public:
    CachingWorker(const char *url, char outfilename[4096], bool needs_output, bool check);
    CachingWorker(const char *url, char outfilename[4096], bool needs_output, bool check, int index);
    CachingWorker();
    ~CachingWorker();

    char  file_name[4096];
    char* file_url;
    bool output_text;
    bool check_file;
    int connection_state;

public slots:
    void process();

signals:
    void finished();
    void finished(int index);
    void error(QString err);

private:
    int OP_index;

};
#endif // CACHINGWORKER_H
