//
// Created by alin on 12/21/16.
//

#include "Server.h"
#include "Address.h"
#include <vector>
#ifndef CLIENT_CONNECTIONHANDLER_H
#define CLIENT_CONNECTIONHANDLER_H

#endif //CLIENT_CONNECTIONHANDLER_H

class ConnectionHandler
{
private:
    Server server;
    ConnectionHandler();
public:
    /**
     * populates the private member server
     * inside the object, to be further used
     * for server communication
     * @param serverAddress
     * @return 0 in case of successful connection
     *         -1 otherwise, errno set appropriately
     */
    int connectToServer(Address serverAddress);

    Server& getServer();

    static ConnectionHandler* getInstance();

};