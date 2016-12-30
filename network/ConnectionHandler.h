//
// Created by alin on 12/21/16.
//
#pragma once
#include "Server.h"
#include "Address.h"
#include "PeerConnection.h"
#include "DownloadPeer.h"
#include <vector>
#ifndef CLIENT_CONNECTIONHANDLER_H
#define CLIENT_CONNECTIONHANDLER_H

#endif //CLIENT_CONNECTIONHANDLER_H
#define LISTENING_PORT 45678
class ConnectionHandler
{
private:
    static ConnectionHandler* instance;
    Server* server;
    int publicIP; //maybe i'll use it
    void _acceptNATTraversal(Address& a);
    ConnectionHandler();
    void _startService();
    bool alive;
public:
    void startService();
    /**
     * populates the private member server
     * inside the object, to be further used
     * for server communication
     * @param serverAddress
     * @return 0 in case of successful connection
     *         -1 otherwise, errno set appropriately
     */
    int connectToServer(Address serverAddress);
    /**
     * wii try to connect to both local and
     * public address
     * throw exception if he cant
     * @param a
     * @return
     */
    DownloadPeer * connectToPeer(Address a);

    /**
     * attempts to traverse the NAT of the peer
     * @param a
     * @return
     */
    DownloadPeer * attemptNATTraversal(Address a);

    /**
     * will call another thread to do it's job
     * @tag thread
     * @param a
     */
    void acceptNATTraversal(Address& a);

    Server& getServer();

    static ConnectionHandler* getInstance();

    unsigned int getPrivateIP();
};