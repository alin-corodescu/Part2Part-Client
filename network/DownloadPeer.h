//
// Created by alin on 12/28/16.
//
#pragma once
#ifndef CLIENT_DOWNLOADPEER_H
#define CLIENT_DOWNLOADPEER_H


#include "PeerConnection.h"

class DownloadPeer : public PeerConnection {
public:
    DownloadPeer(int socket);

protected:
    virtual int _start() override;
    virtual void listenForCommand() override;

private:
    char* dst; //set in constructor
    void request();
    void downloadFile();
};


#endif //CLIENT_DOWNLOADPEER_H
