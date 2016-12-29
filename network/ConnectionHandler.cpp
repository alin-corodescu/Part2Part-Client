//
// Created by alin on 12/28/16.
//


#include <NetworkWrappers.h>
#include <CommandBuilder.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "ConnectionHandler.h"
#include "NATTraversalUtils.h"
#include "UploadPeer.h"

DownloadPeer * ConnectionHandler::connectToPeer(Address a) {
    int socketDescriptor;
    int ip = a.getPublicIP();
    short port = a.getPublicPort();
    socketDescriptor = connectTo(ip,port);
    if (socketDescriptor == -1)
    {
        if (ip == publicIP) {
            //if they are in the same NAT
            int privateIp = a.getPrivateIP();
            short privatePort = a.getPrivatePort();

            socketDescriptor = connectTo(privateIp,privatePort);
            if (socketDescriptor == -1)
            {
                throw "Unable to connect";
            }
        }
    }
    //connection established
    DownloadPeer *peer = new DownloadPeer(socketDescriptor);
    return peer;
}

DownloadPeer * ConnectionHandler::attemptNATTraversal(Address a){

    int accepter, requester, server;
    accepter = NATTraversalUtils::reusableSocket();
    requester = NATTraversalUtils::reusableSocket();
    server = NATTraversalUtils::reusableSocket();

    //replace with a getUsablePort
    NATTraversalUtils::PORT++; //concurrency problems here

    NATTraversalUtils::obtainNATPort(a, server);

    int connectedSocket = NATTraversalUtils::holePunch(a, accepter, requester);

    if (connectedSocket == -1)
        throw "Unable to connect";

    DownloadPeer *peer = new DownloadPeer(connectedSocket);

    return peer;
}

void ConnectionHandler::_acceptNATTraversal(Address &a) {
    int accepter, requester, server;
    accepter = NATTraversalUtils::reusableSocket();
    requester = NATTraversalUtils::reusableSocket();
    server = NATTraversalUtils::reusableSocket();

    NATTraversalUtils::PORT++; //concurrency problems here

    NATTraversalUtils::notify(a, server); //now it's time to begin the punching

    int connectedSocket = NATTraversalUtils::holePunch(a,requester,accepter);

    if (connectedSocket == -1)
        throw "Unable to connect";
    UploadPeer *peer = new UploadPeer(connectedSocket);

    peer->start();
}

Server &ConnectionHandler::getServer() {
    return *server;
}

int ConnectionHandler::connectToServer(Address serverAddress) {
    unsigned int ip = serverAddress.getPublicIP();
    unsigned short port = serverAddress.getPublicPort();

    unsigned int privateIP = getPrivateIP();
    int socket = connectTo(ip,port);

    server = new Server(socket,serverAddress);

    server->processCommandQueue();

    CommandBuilder commandBuilder;
    commandBuilder.setType(JOIN);
    commandBuilder.addArgument((unsigned short)LISTENING_PORT);
    commandBuilder.addArgument(privateIP);
    Command join = commandBuilder.build();
    server->executeCommand(join);
    publicIP = server->getPublicIP();

    server->listenForCommands();

}

unsigned int ConnectionHandler::getPrivateIP() {
    unsigned int privateIP;
    struct ifaddrs *addrs;
    struct ifaddrs *cpy;
    getifaddrs(&addrs);
    cpy = addrs;
    while (addrs)
    {
        if (addrs->ifa_addr && addrs->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)addrs->ifa_addr;
            if (strcmp(inet_ntoa(pAddr->sin_addr), "127.0.0.1")) {
                privateIP = ntohl(pAddr->sin_addr.s_addr);
                freeifaddrs(addrs);
                return privateIP;
            }
        }
        addrs = addrs->ifa_next;
    }

    freeifaddrs(cpy);
    return 0;
}

ConnectionHandler *ConnectionHandler::getInstance() {
    if (instance == NULL)
        instance = new ConnectionHandler();
    return instance;
}

ConnectionHandler::ConnectionHandler() {

}

void ConnectionHandler::_startService() {
    int listeningSocket;
    int val = 1;

    listeningSocket = socket(AF_INET,SOCK_PACKET,0);
    setsockopt(listeningSocket,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = LISTENING_PORT;

    if (bind(listeningSocket,(struct sockaddr*) &addr,sizeof(struct sockaddr)) == -1)
    {
        throw "Bind failed";
    }

    //now the socket is bound

    while (alive)
    {
        int peer;
        sockaddr_in peer_addr;
        socklen_t length;
        peer = accept(listeningSocket,(struct sockaddr*) &peer_addr, &length);
        if (peer == -1)
            continue;

        UploadPeer *uploadPeer = new UploadPeer(peer);
        uploadPeer->start();
    }




}

void ConnectionHandler::startService() {
    alive = 1;
    //TODO: start a thread with _startService here

}
