#include"creaJson.h"












vector<string>  creaJson::dividirBits(string strVideo, int tamanoBytesDeBloque) { //llega el string con los bits del video, y el tamano en bytes que se quiere tener en cada bloque
    int tamanoIndicesDelBloque = tamanoBytesDeBloque; //cantidad de indices (bytes) que tendra cada bloque

    int tamanoDeString = strVideo.length();     //tamano del string del video en longitud
    vector<string> arrayBloques;                //crea el vector

    string tempBloque = "";                       //string de bloque temporal. Crea cada bloque, lo guarda en el vector y reinicia la variable
    int contBytesPorBloque = 0;                   //cuenta los bytes guarados en el string tempBloque

    for (int i = 0; i < tamanoDeString; i++) {        //itera todo el string de bytes del video

        if (contBytesPorBloque !=
            tamanoIndicesDelBloque) {   //verifica si aun no ha llenado el bloque con los bytes que debe llenar el bloque
            tempBloque += strVideo[i];            //guarda el byte en string temporal del bloque
            contBytesPorBloque++;
            if (i == tamanoDeString -  1) {           //si ya esta en el ultimo bit del string del video guarda el actual bloque sin importar que tan lleno este
                arrayBloques.push_back(tempBloque);
            }
        } else {
            arrayBloques.push_back(tempBloque);     //guarda el bloque en el vector
            contBytesPorBloque = 0;
            tempBloque = "";
            i--;
        }
    }
    return arrayBloques;
}




creaJson::creaJson(){}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
std::string creaJson::LoadVideo(std::string filename){
    std::ifstream file(filename,std::ios::binary);
    std::vector<byte> vector((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    std::string str(vector.begin(),vector.end());
    file.close();
    return str;
}

json creaJson::crearMiJson(std::string strVideoBinario, std::string metadata){ //introduce al json: el string del video en binario  y la metadata en el json y retorna el json
    json j;
    j["data"]=strVideoBinario;
    j["metadata"]=metadata;
    j["command"]="C";
    return j;
}

string creaJson::jsonToString(json j){
    string strJson = j.dump(); //convierte el json a string
    return strJson;
}

//Pasa de unsigned charactes a un string de binario
std::string creaJson::toBinary(std::string uCharBytes)
{
    std::string string;
    std::string bits;
    for (int i = 0; i < uCharBytes.size(); i++) {
        bits = std::bitset<8>(uCharBytes[i]).to_string();
        string+=bits;
    }
    return string;
}

string creaJson::titulo(string videoPath){ //itera el path y hagarra solo el titulo del video y lo retorna en string
    int indiceBarraFinal =0;
    int indicePunto=0;

    for(int i=0; i<videoPath.length(); i++){
        string barra="/";
        string punto=".";

        if (videoPath[i] ==barra[0]){
            indiceBarraFinal=i;
        }
        if (videoPath[i] == punto[0]){
            indicePunto=i;
            break;
        }
    }
    string titulo="";
    for (int i=0; i<videoPath.length(); i++){
        if(i>indiceBarraFinal){
            if(i<indicePunto){
                titulo+=videoPath[i];
            }
        }
    }
    return titulo;
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////



string creaJson::buscaryCargarVideo(string videoPath){
    //con la interfaz busca la carpeta y selecciona el video

    string strVideoBits=toBinary(LoadVideo(videoPath)); //carga el video y convierte a bytes y a string y a bits

    string metaData=titulo(videoPath);  //crea el titulo


    json json1= crearMiJson(strVideoBits,metaData);

    string strjson1= jsonToString(json1);

    //json j = json::parse(strjson1);
    //cout << j["metadata"]<<endl;
    //cout << strjson1 << endl;

    json j;
    j["data"]="1234";
    j["metadata"]="meta";
    j["command"]="C";

    string prueba= jsonToString(j);


    //enviar el string strJson1 por socket
    return prueba;// strjson1;

}

string creaJson::metodoPrueba(vector<string> vec){
    json js;
    js["command"]="C";
    js["parts"]=vec.size();
    std::string string2use = js.dump();
    return string2use;
}

