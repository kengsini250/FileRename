//
// Created by oppai on 2023/5/12.
//

#ifndef FILERENAME_MYLISTWIDGET_H
#define FILERENAME_MYLISTWIDGET_H

#include <QListWidget>
#include <QString>
#include <QMap>

//QListWidgeItem
struct ListWidgetFormat
{
    QString currFileName;
    QString currFilePath;
    QString currFilePathWithName;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MyListWidget; }
QT_END_NAMESPACE

class MyListWidget : public QListWidget {
Q_OBJECT

public:
    explicit MyListWidget(QWidget *parent = nullptr);
    ~MyListWidget() override;

    void addFiles(const ListWidgetFormat& f);

    Q_SIGNALS: void currFileSendToMain(const ListWidgetFormat& f);
public slots:
    //预览
    void Preview(const QModelIndex& index);
private:
    Ui::MyListWidget *ui;
    QList<ListWidgetFormat> files;
    int currFilePos=0;
};


#endif //FILERENAME_MYLISTWIDGET_H
