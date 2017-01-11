//
// Created by alin on 12/21/16.
//
#pragma once
#ifndef CLIENT_PEERCONNECTION_H
#define CLIENT_PEERCONNECTION_H

#include <FileDescription.h>
/**
 * class represinting an active connection
 * to a peer
 */
class PeerConnection {
protected:
    FileDescription *fileDescription;
public:
    virtual void setFileDescription(FileDescription*);
    PeerConnection(FileDescription* fileDescription = NULL);

protected:
    int socketDescriptor;
public:
    void setSocketDescriptor(int socketDescriptor);

protected:
    virtual void _sendCommand(Command* command);
    virtual void listenForCommand() = 0;
    virtual int _start() = 0;
public:
    //will run on a new thread
    virtual void start();

};


#endif //CLIENT_PEERCONNECTION_H
