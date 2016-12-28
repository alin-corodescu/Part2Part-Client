//
// Created by alin on 12/27/16.
//

#include "PeerConnector.h"
#include "ConnectionHandler.h"
#include "DownloadPeer.h"

void PeerConnector::start()
{
    /**
     * starts a new thread which will
     * attempt to connect to peers
     * in order to obtain the file
     */
    //create the thread object with _attemptConnections();
    return;
}

void PeerConnector::_attemptConnections() {
    //i'm on a new thread, can block if i need to
    ConnectionHandler *connectionHandler = ConnectionHandler::getInstance();
    int i = 0;
    for (i = 0; i <addresses.size(); i++)
    {
        try{
            DownloadPeer peer = connectionHandler->connectToPeer(addresses[i]);
        }
    }
}

PeerConnector::PeerConnector(FileDescription fileDescription, std::vector<Address> addresses) {
    this->fileDescription = fileDescription;
    this->addresses = addresses;
}

