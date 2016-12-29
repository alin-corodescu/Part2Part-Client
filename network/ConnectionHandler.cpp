//
// Created by alin on 12/28/16.
//


#include <NetworkWrappers.h>
#include <netinet/in.h>
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
