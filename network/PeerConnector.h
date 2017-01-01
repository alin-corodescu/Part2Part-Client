//
// Created by alin on 12/27/16.
//
#pragma once
#ifndef CLIENT_PEERCONNECTOR_H
#define CLIENT_PEERCONNECTOR_H


#include <FileDescription.h>
#include <vector>
#include <Address.h>

class PeerConnector {
private:
    FileDescription fileDescription;
    std::vector<Address> addresses;
    void _attemptConnections();
public:
    PeerConnector(FileDescription *fileDescription,
                    std::vector<Address> addresses);

    /**
     * will create a new thread which will attempt connections
     */
    void start();
};


#endif //CLIENT_PEERCONNECTOR_H
