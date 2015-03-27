#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include <QWidget>
#include <QtWidgets>

class OptionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OptionWidget(QWidget *parent = 0);
    ~OptionWidget();

signals:

public slots:
    void deleteCache();
    void refreshCacheSize();

private:
    QVBoxLayout *layoutMain;
    QHBoxLayout *layoutCache;
    QLabel *label_cache_value;
    QPushButton *delete_cache;
    QPushButton *refresh_cache;
};

#endif // OPTIONWIDGET_H
