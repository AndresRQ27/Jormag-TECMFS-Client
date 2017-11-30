#ifndef UPLOAD_H
#define UPLOAD_H

#include "mainwindow.h"
#include "json.hpp"
#include "tcp_client.h"
#include <QString>
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

class Upload
{
public:
    Upload();
    Upload(QStringList videoList, QStringList jsonList, tcp_client client);
    ~Upload();

    void SendFiles();

private:
    QStringList videoList, jsonList;
    tcp_client client;
};

#endif // UPLOAD_H
