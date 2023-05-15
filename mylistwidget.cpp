//
// Created by oppai on 2023/5/12.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MyListWidget.h" resolved

#include "mylistwidget.h"
#include "ui_MyListWidget.h"
#include <QMenu>
#include <QLabel>
#include <QFileInfo>

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

    //改名
    connect(this,&QListWidget::clicked,this,[this](const QModelIndex& index){
        currFilePos = index.row();
        Q_EMIT currFileSendToMain(files[currFilePos]);
    });

    //预览
    connect(this,&QListWidget::doubleClicked,this,&MyListWidget::Preview);

}

MyListWidget::~MyListWidget() {
    delete ui;
}

void MyListWidget::addFiles(const ListWidgetFormat& f)
{
    if(f.currFileName == "" && f.currFilePath == "" && f.currFilePathWithName == ""){
        //end -> update list widget
        clear();
        for(auto&file:files){
            addItem(file.currFileName);
        }
    }
    else{
        files.append(f);
    }
}

void MyListWidget::Preview(const QModelIndex &index) {
    currFilePos = index.row();
//    QFileInfo info(files[currFilePos].currFilePathWithName);

    const int W = 400;
    const int H = 300;
    auto picWidget = new QWidget;
    picWidget->setGeometry(QCursor::pos().x(),QCursor::pos().y(),W,H);
    auto picLabel = new QLabel(picWidget);
    picLabel->setGeometry(0,0,W,H);
    QImage img(files[currFilePos].currFilePathWithName);
    if(img.isNull()){
        return ;
    }

    int picWidth = img.width();
    int picHeight = img.height();
    if(picWidth == picHeight)
        picLabel->setPixmap(QPixmap::fromImage(img.scaled(picLabel->size())));
    if(picWidth>picHeight){
        float pW_W = picWidth/W;
        picLabel->setPixmap(QPixmap::fromImage(img.scaled(W,picHeight/pW_W)));
    }
    if(picWidth<picHeight){
        float pH_H = picHeight/H;
        picLabel->setPixmap(QPixmap::fromImage(img.scaled(picWidth/pH_H,H)));
    }

    picWidget->show();
}

void MyListWidget::updateListWidget(const ListWidgetFormat& f) {
    files[currFilePos] = f;
    clear();
    for(auto&file:files){
        addItem(file.currFileName);
    }
}

