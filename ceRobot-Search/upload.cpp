#include "upload.h"

#include <iostream>
#include <fstream>

Upload::Upload(){}

void Upload::SendFiles(QStringList videoList, tcp_client client)
{ 
    json commandJSON;
    commandJSON["command"] = "C";
    commandJSON["data"];
    commandJSON["metadata"];

    for(int i = 0; i < videoList.length(); ++i){
        QString qs = videoList.at(i);
        std::string path = qs.toUtf8().constData();

        if(!client.send_data(commandJSON.dump().c_str())){
            throw std::system_error();
        }
    }
}
