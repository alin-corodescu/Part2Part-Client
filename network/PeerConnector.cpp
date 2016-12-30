//
// Created by alin on 12/27/16.
//
#pragma once
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
            DownloadPeer *peer = connectionHandler->connectToPeer(addresses[i]);
            peer->setFileDescription(fileDescription);
            peer->start();//ce fac in cazul in care imi da resource not found?
            //cazul in care ma conectez din greseala la un pc local
            //TODO : treat this case
            break;
        }
        catch(...)
        {
            continue;
        }
    }
    if (i == addresses.size())
    {
        for (i = 0; i <addresses.size(); i++)
        {
            try{
                DownloadPeer *peer = connectionHandler->attemptNATTraversal(addresses[i]);
                peer->setFileDescription(fileDescription);
                peer->start();
                break;
            }
            catch(...)
            {
                continue;
            }
        }
    }
    if (i == addresses.size())
    {
        //aiurea, nu ma pot conecta;
    }
}

PeerConnector::PeerConnector(FileDescription *fileDescription, std::vector<Address> addresses) : fileDescription(*fileDescription) {
    this->addresses = addresses;
}

