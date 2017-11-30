//
// Created by sebas97012 on 9/28/17.
//

#include "tcp_client.h"

tcp_client::tcp_client()
{
    sock = -1;
    port = 0;
    address = "";
}

/**
    Connect to a host on a certain port number
*/
bool tcp_client::conn(std::string address , int port)
{
    //create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }

        std::cout<<"Socket created\n";
    }
    else    {   /* OK , nothing */  }

    //setup address structure
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;

        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            herror("gethostbyname");
            std::cout<<"Failed to resolve hostname\n";

            return false;
        }

        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];

            std::cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<std::endl;

            break;
        }
    }

        //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }

    server.sin_family = AF_INET;
    server.sin_port = htons( port );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    std::cout<<"Connected\n";
    return true;
}

/**
    Send data to the connected host
*/
bool tcp_client::send_data(const char* data)
{
    //Send some data
    if( send(sock , data, strlen(data), 0) < 0)
    {
        perror("Send failed : ");
        return false;
    }
    std::cout<<"Data send\n";
    usleep(200);
    return true;
}

/**
    Receive data from the connected host
*/
std::__cxx11::string tcp_client::receive()
{
    char buffer[BUFFER_SIZE];

    //Receive a reply from the server
    if( recv(sock , buffer , BUFFER_SIZE , 0) < 0)
    {
        puts("recv failed");
    }

    //std::cout<<std::__cxx11::string(buffer);
    return std::__cxx11::string(buffer);
}
