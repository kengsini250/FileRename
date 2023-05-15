//
// Created by oppai on 2023/5/12.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MyListWidget.h" resolved

#include "mylistwidget.h"
#include "ui_MyListWidget.h"
#include <QMenu>

MyListWidget::MyListWidget(QWidget *parent) :
        QListWidget(parent), ui(new Ui::MyListWidget) {
    ui->setupUi(this);
    setMinimumSize(457,431);
    resize(457,431);

    //右击菜单
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&QListWidget::customContextMenuRequested,this,[this](const QPoint &pos) {

        auto *menu = new QMenu(this);
        QAction *actionDelete = menu->addAction("delete");
        menu->addAction(actionDelete);
        connect(actionDelete,&QAction::triggered,this,[this]{
            files.remove(currFilePos);
            takeItem(currFilePos);
        });
        menu->exec(QCursor::pos());
    });

    connect(this,&QListWidget::clicked,this,[this](const QModelIndex& index){
        currFilePos = index.row();
    });

    connect(this,&QListWidget::doubleClicked,this,[this](const QModelIndex& index){
        currFilePos = index.row();
        Q_EMIT currFileSendToMain(files[currFilePos]);
    });

}

MyListWidget::~MyListWidget() {
    delete ui;
}

void MyListWidget::addFiles(const ListWidgetFormat& f)
{
    if(f.currFileName == "" && f.currFilePath == "" && f.currFilePathWithName == ""){
        //end -> update list widget
        for(auto&file:files){
            addItem(file.currFileName);
        }
    }
    else
        files.append(f);
}

