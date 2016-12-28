//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_PEERCONNECTION_H
#define CLIENT_PEERCONNECTION_H

#include <FileDescription.h>
#define UPLOADER 1
#define DOWNLOADER 2
/**
 * class represinting an active connection
 * to a peer
 */
class PeerConnection {
protected:
    FileDescription fileDescription;
    int socketDescriptor;
    virtual void _sendCommand(Command command);
    virtual void listenForCommand() = 0;
    virtual void _start() = 0;
public:
    //will run on a new thread
    virtual void start();
};


#endif //CLIENT_PEERCONNECTION_H
