#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->status->setText("Status: Hello World");
    //client.conn("127.168.0.1", 8080);

    //Hide search elements
    ui->chooseComboBox->hide();
    ui->pushChooseButton->hide();
    ui->search->hide();
    ui->textSearch->hide();
    ui->pushSearchButton->hide();
    ui->backButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_uploadButton_clicked()
{
    QStringList jsonList, videoList;


    videoList = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more videos to upload",
                            "/home",
                            "(*.mp4)");

    while (true){
        jsonList = QFileDialog::getOpenFileNames(
                    this,
                    "Select the corresponding json files to upload",
                    "/home",
                    "(*.json)");

        if (videoList.length() != jsonList.length()){
            ui->status->setText("Status: Error uploading");
            qDebug() << "The number of json selected don't match the number of videos uploaded";
        } else {
            break;
        }
    }

    Upload upload = Upload(videoList, jsonList, this->client);
}

void MainWindow::on_searchButton_clicked()
{
    //Hide main elements
    ui->title->hide();
    ui->status->hide();
    ui->searchButton->hide();
    ui->uploadButton->hide();

    //Show search elements
    ui->chooseComboBox->show();
    ui->pushChooseButton->show();
    ui->search->show();
    ui->textSearch->show();
    ui->pushSearchButton->show();
    ui->backButton->show();


}

void MainWindow::on_backButton_clicked()
{
    //Hide search elements
    ui->chooseComboBox->hide();
    ui->pushChooseButton->hide();
    ui->search->hide();
    ui->textSearch->hide();
    ui->pushSearchButton->hide();
    ui->backButton->hide();

    //Show main elements
    ui->title->show();
    ui->status->show();
    ui->searchButton->show();
    ui->uploadButton->show();
}
