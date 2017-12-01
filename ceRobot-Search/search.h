#ifndef SEARCH_H
#define SEARCH_H

#include "mainwindow.h"
#include "json.hpp"
#include "tcp_client.h"
#include <QString>
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

class Search
{
public:
    Search();
    static void Request(tcp_client client);
    static list<string> Receive(tcp_client client);
};

#endif // SEARCH_H
