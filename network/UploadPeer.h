//
// Created by alin on 12/28/16.
//

#ifndef CLIENT_UPLOADPEER_H
#define CLIENT_UPLOADPEER_H


#include "PeerConnection.h"

class UploadPeer : public PeerConnection {
private:
    char* path;
protected:
    virtual void listenForCommand() override;

    virtual void _start() override;

    virtual void uploadFile();
};


#endif //CLIENT_UPLOADPEER_H
