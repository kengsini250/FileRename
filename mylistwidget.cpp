//
// Created by oppai on 2023/5/12.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MyListWidget.h" resolved

#include "mylistwidget.h"
#include "ui_MyListWidget.h"


MyListWidget::MyListWidget(QWidget *parent) :
        QListWidget(parent), ui(new Ui::MyListWidget) {
    ui->setupUi(this);
    setMinimumSize(457,431);
    resize(457,431);


    connect(this,&QListWidget::doubleClicked,this,[this](const QModelIndex& index){
        int row = index.row();
        emit currFileSendToMain(files[row]);
    });
}

MyListWidget::~MyListWidget() {
    delete ui;
}

void MyListWidget::addFiles(const ListWidgetFormat& f)
{
    if(f.currFileName == "" && f.currFilePath == "" && f.currFilePathWithName == ""){
        //end -> update listwidget
        for(auto&file:files){
            addItem(file.currFileName);
        }
    }
    else
        files.append(f);
}

