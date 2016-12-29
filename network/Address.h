//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_ADRESS_H
#define CLIENT_ADRESS_H

#endif //CLIENT_ADRESS_H

class Address
{
private:
    unsigned int privateIP;
    unsigned short privatePort;
    unsigned int publicIP;
    unsigned short publicPort;
public:
    void toString();

    unsigned int getPrivateIP() const {
        return privateIP;
    }

    unsigned int getPublicIP() const {
        return publicIP;
    }

    unsigned short getPublicPort() const {
        return publicPort;
    }

    unsigned short getPrivatePort() const {
        return privatePort;
    }

    Address(const char * stringAddr);
    Address(unsigned int publicIP,unsigned short publicPort,
                unsigned int privateIP,unsigned short privatePort);
};