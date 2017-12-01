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
    QStringList videoList;
    videoList = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more videos to upload",
                            "/home",
                            "(*.mp4)");

    try {
        Upload::SendFiles(videoList, this->client);
    } catch (std::system_error &e) {
        ui->status->setText(e.what());
    }
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
    ui->textSearch->clear();

    //Show main elements
    ui->title->show();
    ui->status->show();
    ui->searchButton->show();
    ui->uploadButton->show();
}

void MainWindow::on_pushSearchButton_clicked()
{
    QString searchWord = ui->textSearch->toPlainText();
    std::string str = searchWord.toUtf8().constData();

    list<string> nameList;
    try{
        nameList = Search::Receive(this->client);
    } catch (std::system_error &e) {
        this->on_backButton_clicked();
        ui->status->setText(e.what());
    }

    if(nameList.size() != 0){
        for (int i = 0; i < nameList.size(); ++i) {
            if(nameList.front().find(str) != -1){
                ui->chooseComboBox->addItem(tr(nameList.front().c_str()));
            }
            nameList.pop_front();
        }
    }
}

void MainWindow::on_pushChooseButton_clicked()
{
    string video;
    json commandJSON, videoJSON;
    string text = ui->chooseComboBox->currentText().toUtf8().constData();

    if(text.size() != 0){
        commandJSON["command"] = "v";
        commandJSON["title"] = text;
        client.send_data(commandJSON.dump().c_str());
        video = client.receive();
        videoJSON = json::parse(video);
    }
}
