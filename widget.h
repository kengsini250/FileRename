//
// Created by oppai on 2023/5/5.
//

#ifndef FILERENAME_WIDGET_H
#define FILERENAME_WIDGET_H

#include <QDebug>
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QFileInfo>
#include <QDropEvent>
#include <QDragEnterEvent>
#include "mylistwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

enum Format{Name=1,Date,Time,Comment,Random,FileFormat};
class Widget : public QWidget {
Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

    void InitFormat();
    QString GetFileNameFromFormat();
    void change(Format format,const QString& temp);
private:
    Ui::Widget *ui;
    QTimer *timer;
    QMap<int,QString> All;

    /*
     * QString currFileName,//xxx.jpg
     * currFilePathWithName,// /aaa/bbb/ccc/xxx.jpg
     * currFilePath;// /aaa/bbb/ccc
     */
    QString currFileName,currFilePathWithName,currFilePath;

    MyListWidget* myListWidget;

protected:
    void dropEvent(QDropEvent *event)override;
    void dragEnterEvent(QDragEnterEvent *event)override;
};


#endif //FILERENAME_WIDGET_H
