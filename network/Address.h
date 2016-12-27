//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_ADRESS_H
#define CLIENT_ADRESS_H

#endif //CLIENT_ADRESS_H

class Address
{
private:
    int privateIP;
    short privatePort;
    int publicIP;
    short publicPort;
public:
    void toString();

    int getPrivateIP() const {
        return privateIP;
    }

    int getPublicIP() const {
        return publicIP;
    }

    short getPublicPort() const {
        return publicPort;
    }

    short getPrivatePort() const {
        return privatePort;
    }

    Address(const char * stringAddr);
    Address(unsigned int publicIP,unsigned short publicPort,
                unsigned int privateIP,unsigned short privatePort);
};