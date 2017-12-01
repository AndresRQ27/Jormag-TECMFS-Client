#include "upload.h"
#include "creaJson.h"

#include <iostream>
#include <fstream>

Upload::Upload(){}

void Upload::SendFiles(QStringList videoList, tcp_client client)
{ 
    for(int i = 0; i < videoList.length(); ++i){
        QString qs = videoList.at(i);
        std::string path = qs.toUtf8().constData();

        creaJson creaj;
        //string strJson = creaj.buscaryCargarVideo(path);

        string str = creaj.toBinary(creaj.LoadVideo(path));
        vector<string> vec= creaj.dividirBits(str,800);

        string a= creaj.metodoPrueba(vec);
        

        //cout<<js["parts"]<<endl;
        if(!client.send_data(a.c_str())){
            throw std::system_error();
        }
    }
}
