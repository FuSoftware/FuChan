#ifndef CATALOGWIDGET_H
#define CATALOGWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QThread>
#include <ostream>
#include <iomanip>

#include "../fonctions_json.h"
#include "post_widget.h"
#include "catalog_op_widget.h"

class CatalogWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CatalogWidget(QWidget *parent = 0);
    ~CatalogWidget();

    std::string getBoard();
    std::string generateBoardLabel(std::string board, std::string title);


signals:
    void load_query(int thread_index);

public slots:
    void downloadCatalog();

    void thread_load_toggled(int i);
    void startLoadingOPs(QString string);
    void startDownloadThumbnails();
    void loadOP(int index);

private:
    QSignalMapper *mapper;

    QVBoxLayout *layoutMain;
    QComboBox *comboBoxSelectBoard;

    QScrollArea *scrollArea;
    QWidget *areaWidget;
    QGridLayout *layoutPosts;
    QList<CatalogOpWidget*> catalog_op_widgets;
    QList<QThread*> thumb_threads;
    QList<CachingWorker*> thumb_workers;

    std::vector<int> catalog_op_ids;
    std::vector<Post*> thread_ops;
    std::vector<std::string> board_labels;
    std::vector<std::string> board_list;
    std::string board;
    std::string url;
    std::string outfilename;

    QThread *qThread;
    CachingWorker *worker;

    int page_number;
    int post_number;
    int post_total;
    int loaded_posts;

};

#endif // CATALOGWIDGET_H
