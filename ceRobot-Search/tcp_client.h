//
// Created by sebas97012 on 9/28/17.
//

#ifndef RMLib_TCP_CLIENT_H
#define RMLib_TCP_CLIENT_H
#include<iostream>    //cout
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<string>  //string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent
#include <utility>
#include "unistd.h"

#define BUFFER_SIZE 1024
enum command{init,new_,get};
/**
    TCP Client class
*/
class tcp_client
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;

public:
    tcp_client();
    bool conn(std::string ip, int port);
    bool send_data(const char* data);
    std::string receive();
};

#endif //RMLib_TCP_CLIENT_H
