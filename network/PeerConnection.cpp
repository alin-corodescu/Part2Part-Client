//
// Created by alin on 12/21/16.
//

#include <CommandBuilder.h>
#include <thread>
#include "PeerConnection.h"


void PeerConnection::_sendCommand(Command command) {

}

void PeerConnection::setSocketDescriptor(int socketDescriptor) {
    PeerConnection::socketDescriptor = socketDescriptor;
}

void PeerConnection::setFileDescription(const FileDescription &fileDescription) {
    PeerConnection::fileDescription = new FileDescription(fileDescription);
}

PeerConnection::PeerConnection(FileDescription *fileDescription) {
    if (fileDescription != NULL)
        this->fileDescription = new FileDescription(*fileDescription);

}

void PeerConnection::start() {
    std::thread([=] {_start();});
}
