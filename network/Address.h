//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_ADRESS_H
#define CLIENT_ADRESS_H

#endif //CLIENT_ADRESS_H

class Address
{
private:
    int ipAdress;
    short port;
public:
    int getIpAdress();
    int getPort();

    void toString();

    Address(const char * stringAddr);
    Address();
};