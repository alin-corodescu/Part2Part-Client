//
// Created by alin on 12/29/16.
//

#include "Address.h"

Address::Address(unsigned int publicIP,unsigned short publicPort,
        unsigned int privateIP,unsigned short privatePort)
{
    this->publicIP = publicIP;
    this-> privateIP = privateIP;
    this->publicPort = publicPort;
    this->privatePort = privatePort;
}
