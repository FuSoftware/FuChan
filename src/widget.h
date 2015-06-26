#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "Widget/thread_widget.h"
#include "Widget/board_select_widget.h"
#include "Widget/viewer_widget.h"
#include "Widget/closable_tab_widget.h"
#include "Widget/option_widget.h"
#include "Widget/catalog_widget.h"

#include "json/json.h"
#include "fonctions_json.h"
#include "fonctions.h"

class ThreadWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void setTab(int index);
    void loadFavourites();

    ViewerWidget *viewer_widget;
    ClosableTabWidget *tab_widget;

public slots:
    void loadThread(int thread_index);
    void loadThread();

private:
    BoardSelectWidget *select_widget;
    ThreadWidget *thread_widget;
    OptionWidget *option_widget;
    CatalogWidget *catalog_widget;

    QTextBrowser *textBrowserLog;
};

#endif // WIDGET_H
