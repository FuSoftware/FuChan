#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "post.h"

class ViewerWidget: public QWidget
{
    Q_OBJECT
public:
    ViewerWidget(QWidget *parent = 0);
    ~ViewerWidget();
    void download_picture(Post *post, bool download);

public slots:
    void load_picture(Post *post);
    void download_picture_persistent();

private:
    bool image_loaded;

    Post* local_post;

    QHBoxLayout *mainlayout;
    QVBoxLayout *secondaryLayout;

    QPushButton *download_button;

    QLabel *labelImage;

    QGroupBox *groupBoxInfo;
        QVBoxLayout *layoutGroupBox;
            QLabel *labelInfo[16];
};

#endif // VIEWERWIDGET_H
