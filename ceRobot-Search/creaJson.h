#ifndef CREAJSON_H
#define CREAJSON_H

#include <iostream>
#include <fstream>
#include "json.hpp"
#include <bitset>

typedef unsigned char byte;
using json = nlohmann::json;
using namespace std;

class creaJson
{
public:
    creaJson();
    string buscaryCargarVideo(string videoPath);
    std::string  toBinary(std::string uCharBytes);
    std::string LoadVideo(std::string filename);

    std::vector<string>  dividirBits(string strVideo, int tamanoBytesDeBloque);

    std::string metodoPrueba(vector<string>);


private:

    json crearMiJson(std::string strVideoBinario, std::string metadata);
    string jsonToString(json j);

    string titulo(string videoPath);
};

#endif // CREAJSON_H
