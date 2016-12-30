//
// Created by alin on 12/29/16.
//
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include "Address.h"

Address::Address(unsigned int publicIP,unsigned short publicPort,
        unsigned int privateIP,unsigned short privatePort)
{
    this->publicIP = publicIP;
    this-> privateIP = privateIP;
    this->publicPort = publicPort;
    this->privatePort = privatePort;
}

Address::Address(const char *stringAddr) {
    char* buffer;
    buffer = (char*) malloc(strlen(stringAddr));
    char * p;
    p = strtok(buffer,":");

    unsigned int ip = inet_addr(p);
    publicIP = ntohl(ip);

    p = strtok(NULL,":");
    unsigned short port = (unsigned short) atoi(p);
    publicPort = port;



}

void Address::toString() {


}
