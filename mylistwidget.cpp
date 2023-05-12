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
}

MyListWidget::~MyListWidget() {
    delete ui;
}

