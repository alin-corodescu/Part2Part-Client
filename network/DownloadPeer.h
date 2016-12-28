//
// Created by alin on 12/28/16.
//

#ifndef CLIENT_DOWNLOADPEER_H
#define CLIENT_DOWNLOADPEER_H


#include "PeerConnection.h"

class DownloadPeer : public PeerConnection {

protected:
    virtual void _start() override;
    virtual void listenForCommand() override;

private:
    char* dst; //set in constructor
    void request();
    void downloadFile();
};


#endif //CLIENT_DOWNLOADPEER_H
