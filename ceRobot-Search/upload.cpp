#include "upload.h"

#include <iostream>
#include <fstream>

Upload::Upload(){}

Upload::Upload(QStringList videoList, QStringList jsonList, tcp_client client)
{
    this->videoList = videoList;
    this->jsonList = jsonList;
    this->client = client;
}

void Upload::SendFiles()
{
    string data;
    for(int i = 0; i < jsonList.length(); ++i){
        string line;
        QString qs = jsonList.at(i);
        std::string path = qs.toUtf8().constData();
        ifstream myfile(path);
        if (myfile.is_open())
          {
            while (getline(myfile,line))
            {
              data.append(line);
            }
          } else cout << "Unable to open file";
        myfile.close();
    }
    const char *cstr = data.c_str();
    client.send_data(cstr);
}

Upload::~Upload(){

}
