#ifndef CLOSABLETABWIDGET_H
#define CLOSABLETABWIDGET_H

#include <QtWidgets>


class ClosableTabWidget : public QTabWidget
{
    Q_OBJECT
public:
        ClosableTabWidget(QWidget* parent)
        {
            this->setParent(parent);
            connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
        }
        ~ClosableTabWidget(){}



public slots:
        void closeTab(int index)
        {
            //Handle tabCloseRequested Signal and Close the Tab
            if(index>2)
            {
                this->removeTab(index);
            }
        }
};

#endif // CLOSABLETABWIDGET_H
