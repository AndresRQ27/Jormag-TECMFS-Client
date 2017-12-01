#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcp_client.h"
#include "upload.h"
#include "search.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_uploadButton_clicked();

    void on_searchButton_clicked();

    void on_backButton_clicked();

    void on_pushSearchButton_clicked();

    void on_pushChooseButton_clicked();

private:
    Ui::MainWindow *ui;
    tcp_client client;
};

#endif // MAINWINDOW_H
