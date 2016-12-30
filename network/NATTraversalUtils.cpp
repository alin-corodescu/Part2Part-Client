//
// Created by alin on 12/28/16.
//
#include <CommandBuilder.h>
#include <NetworkWrappers.h>
#include <unistd.h>
#include <string.h>
#include <cstdio>
#include "NATTraversalUtils.h"
#include "ConnectionHandler.h"

#define RETRY_LIMIT 5
#define RETRY_INTERVAL 1

unsigned short NATTraversalUtils::PORT = START_PORT;

int NATTraversalUtils::reusableSocket() {
    int optval = 1;

    struct sockaddr_in local;

    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(PORT);

    /*
     * socket descriptori utilizati pentru hole punching,
     * vor folosi acelasi sockaddr_in (local)
     */
    int socketDesc;
    socketDesc = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(socketDesc,SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(socketDesc,SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    bind(socketDesc, (struct sockaddr *) &local, sizeof(struct sockaddr));

    return socketDesc;
}

void NATTraversalUtils::obtainNATPort(Address &a, int socket) {

    unsigned int  ip = a.getPublicIP();
    //establish ephemere server connection
    ConnectionHandler *connectionHandler = ConnectionHandler::getInstance();
    Address serverAddress =  connectionHandler->getServer().getAddress();

    CommandBuilder commandBuilder;
    commandBuilder.setType(NOTIFIY);
    commandBuilder.addArgument(ip);

    Command notification = commandBuilder.build();

    //establish a new connection with the server.
    connectThrough(socket, serverAddress.getPublicIP(),serverAddress.getPublicPort());

    Server *ephemereConnection = new Server(socket,serverAddress);

    ephemereConnection->_executeCommand(notification);

    a = ephemereConnection->listenForOpen();

    return;
}

int NATTraversalUtils::holePunch(Address peer, int requester, int accepter) {

    struct sockaddr_in peer_addr;
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = htonl(peer.getPublicIP());
    peer_addr.sin_port = htons(peer.getPublicPort());

    int connectedSocket = -1;

    fd_set readfds;   /* multimea descriptorilor de citire */
    fd_set actfds;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    FD_ZERO (&actfds);    /* initial, multimea este vida */
    FD_SET (accepter, &actfds);   /* includem in multime socketul creat */
    int nfds = accepter;
    for (int i = 0; i < RETRY_LIMIT; i++)
    {
        socklen_t length =0;
        int status = connect(requester,(struct sockaddr *) &peer_addr, sizeof(struct sockaddr));
        if (status >= 0) {
            connectedSocket = requester;
            break;
        }

        listen(accepter,5);
        sleep(RETRY_INTERVAL);
        bcopy ((char *) &actfds, (char *) &readfds, sizeof (readfds));
        select (nfds+1, &readfds, NULL, NULL, &tv);
        if (FD_ISSET (accepter, &readfds))
        {
            connectedSocket = accept(accepter, (struct sockaddr *) &peer_addr, &length);
            break;
        }
    }

    return connectedSocket;
}

void NATTraversalUtils::notify(const Address &a, int server) {
    unsigned int  ip = a.getPublicIP();
    //establish ephemere server connection
    ConnectionHandler *connectionHandler = ConnectionHandler::getInstance();
    Address serverAddress =  connectionHandler->getServer().getAddress();

    CommandBuilder commandBuilder;
    commandBuilder.setType(NOTIFIY);
    commandBuilder.addArgument(ip);

    Command notification = commandBuilder.build();

    //establish a new connection with the server.
    connectThrough(server, serverAddress.getPublicIP(),serverAddress.getPublicPort());

    Server *ephemereConnection = new Server(server,serverAddress);

    ephemereConnection->_executeCommand(notification);

    delete ephemereConnection;
}

void NATTraversalUtils::connectThrough(int socket, unsigned int ip, unsigned short port) {
    struct sockaddr_in endpoint;
    endpoint.sin_family = AF_INET;
    endpoint.sin_addr.s_addr = htonl(ip);
    endpoint.sin_port = htons(port);

    int status = connect(socket,(struct sockaddr*) &endpoint,sizeof(struct sockaddr));

    if (status < 0 )
    {
        throw "Connection error";
    }

}
