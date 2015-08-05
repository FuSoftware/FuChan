#include "widget.h"
#include <QApplication>

#include "Widget/thread_widget.h"
#include "Widget/board_select_widget.h"
#include "constantes.h"

#include "Utils/download_indexer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion(APP_VERSION);
    a.setApplicationName(APP_NAME);

    cachingFile(BoardURL, BOARD_LIST_PATH, true, false);

    Widget w;
    w.show();
    w.setWindowTitle(QString(APP_NAME) + QString(" ") + QString(APP_VERSION));

    //DownloadIndexer indexer;

    return a.exec();
}
