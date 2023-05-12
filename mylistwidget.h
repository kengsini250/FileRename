//
// Created by oppai on 2023/5/12.
//

#ifndef FILERENAME_MYLISTWIDGET_H
#define FILERENAME_MYLISTWIDGET_H

#include <QListWidget>



QT_BEGIN_NAMESPACE
namespace Ui { class MyListWidget; }
QT_END_NAMESPACE

class MyListWidget : public QListWidget {
Q_OBJECT

public:
    explicit MyListWidget(QWidget *parent = nullptr);

    ~MyListWidget() override;

private:
    Ui::MyListWidget *ui;

};


#endif //FILERENAME_MYLISTWIDGET_H
