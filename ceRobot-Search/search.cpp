#include "search.h"

Search::Search(){}

list<string> Search::Receive(tcp_client client)
{
    string answerString;
    json commandJSON;
    commandJSON["command"]="g";

    if(client.send_data(commandJSON.dump().c_str())){
        answerString = client.receive();
    } else {
        throw std::system_error();
    }

    json answerJSON = json::parse(answerString);
    list<string> nameList = answerJSON["names"];
    return nameList;
}
