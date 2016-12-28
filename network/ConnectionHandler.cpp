//
// Created by alin on 12/28/16.
//


#include <NetworkWrappers.h>
#include "ConnectionHandler.h"

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
                throw 1;
            }
        }
    }
    //connection established
    DownloadPeer *peer = new DownloadPeer(socketDescriptor);
    return peer;
}

DownloadPeer * ConnectionHandler::attemptNATTraversal(Address a) {

}
