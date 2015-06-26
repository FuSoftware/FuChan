#ifndef CATALOGOPWIDGET_H
#define CATALOGOPWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "post.h"
#include "clickableLabel.h"

class CatalogOpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CatalogOpWidget(Post* thread_op, QWidget *parent = 0);
    ~CatalogOpWidget();

signals:
    void thumb_clicked();

public slots:
    void emit_thumb_clicked();

private:
    QVBoxLayout *layoutMain;

    ClickableLabel *thumbnail;
    QLabel *title;

    QHBoxLayout *secondaryLayout;
    QLabel *replies;
    QLabel *images;

    QTextBrowser *comment;
};

#endif // CATALOGOPWIDGET_H
