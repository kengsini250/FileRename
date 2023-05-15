//
// Created by oppai on 2023/5/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Widget.h" resolved

#include "widget.h"
#include "ui_Widget.h"
#include "mylistwidget.h"
#include <QRandomGenerator>
#include <QMimeData>
#include <QList>
#include <QUrl>

Widget::Widget(QWidget *parent) :
        QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    setAcceptDrops(true);

    InitFormat();
    myListWidget = new MyListWidget(ui->frame);

    //update
    //FileName
    connect(ui->lineEdit_Filename,&QLineEdit::textChanged,this,
            [this](const QString&temp){
                change(Name,temp);
                ui->lineEdit->setText(GetFileNameFromFormat());
            });

    //Date
    ui->dateEdit->setDate(QDate::currentDate());
    connect(ui->pushButton_DateEdit,&QPushButton::clicked,this,[this]{
        QString temp = ui->dateEdit->date().toString("yyyy_MM_dd");
        change(Date,temp);
        ui->lineEdit->setText(GetFileNameFromFormat());
    });

    connect(ui->dateEdit,&QDateEdit::dateChanged,this,
            [this](const QDate&temp){
                change(Date,temp.toString("yyyy_MM_dd"));
            });

    //Time
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]{
        ui->timeEdit->setTime(QTime::currentTime());
    });
    timer->start(1000);

    connect(ui->pushButton_TimeEdit,&QPushButton::clicked,this,[this]{
        QString temp = ui->timeEdit->time().toString("hh_mm_ss");
        change(Time,temp);
        ui->lineEdit->setText(GetFileNameFromFormat());
    });


    //comment
    connect(ui->lineEdit_comment,&QLineEdit::textChanged,this,
            [this](const QString&temp){
                change(Comment,temp);
                ui->lineEdit->setText(GetFileNameFromFormat());
            });

    connect(ui->pushButton_Random,&QPushButton::clicked,this,[this]{
        int rand = QRandomGenerator::global()->bounded(0,12345678);
        ui->lineEdit_Random->setText(QString::number(rand));
    });

    connect(ui->lineEdit_Random,&QLineEdit::textChanged,this,
            [this](const QString&temp){
                change(Random,temp);
                ui->lineEdit->setText(GetFileNameFromFormat());
            });

    //file format
    connect(ui->comboBox,&QComboBox::currentIndexChanged,this,
            [this](int index){
        change(FileFormat,ui->comboBox->currentText());
                ui->lineEdit->setText(GetFileNameFromFormat());
    });

    //clean
    connect(ui->pushButton_Clean,&QPushButton::clicked,this,[this]{
        ui->lineEdit->clear();
    });

    //rename
    connect(ui->pushButton_Rename,&QPushButton::clicked,this,[this]{
        if(currFileName == "" || currFilePathWithName == "") return;
        QFile file(currFilePathWithName);
        file.rename(currFilePath + "/" +ui->lineEdit->text());
    });

    //get from listwidget
    connect(myListWidget,&MyListWidget::currFileSendToMain,this,[this](const ListWidgetFormat& f){
        currFilePathWithName = f.currFilePathWithName;
        currFilePath = f.currFilePath;
        currFileName = f.currFileName;
        ui->lineEdit_Display->setText(currFileName);
    });

}

Widget::~Widget() {
    delete ui;
}

void Widget::InitFormat() {
    All.insert(Name,"");
    All.insert(Date,"");
    All.insert(Time,"");
    All.insert(Comment,"");
    All.insert(Random,"");
    All.insert(FileFormat,"");
}

QString Widget::GetFileNameFromFormat() {
    QString FileName;
    for(auto p=All.begin();p!=std::prev(All.end(),1);p++){
        if(p.value()=="")
            continue;
        FileName+=p.value();
        FileName+="_";
    }
    int pos = FileName.lastIndexOf(QChar('_'));
    FileName = FileName.left(pos);

    return FileName + ui->comboBox->currentText();
}

void Widget::change(Format format, const QString &temp) {
    All[format] = temp;
}

void Widget::dropEvent(QDropEvent *event) {
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.empty()){
        return;
    }
    for(auto & url : urls){
        currFilePathWithName = url.toLocalFile();
        int pos = currFilePathWithName.lastIndexOf(QChar('/'));
        currFilePath = currFilePathWithName.left(pos);
        currFileName = currFilePathWithName.mid(pos+1,currFilePathWithName.size()-pos);
        ui->lineEdit_Display->setText(currFileName);

        //send to listwidget
        myListWidget->addFiles({currFileName,currFilePath,currFilePathWithName});
    }
    //send end
    myListWidget->addFiles({"","",""});

    QWidget::dropEvent(event);
}

void Widget::dragEnterEvent(QDragEnterEvent *event) {
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
    QWidget::dragEnterEvent(event);
}
