//
// Created by alin on 12/21/16.
//

#include <CommandBuilder.h>
#include <thread>
#include <IOWrappers.h>
#include "PeerConnection.h"


void PeerConnection::_sendCommand(Command* command) {
    int size;
    size = command->length();
    char *string = (char*) malloc(size);
    command->toString(string);
    writeString( socketDescriptor,string, size);
    free(string);
    delete command;
}

void PeerConnection::setSocketDescriptor(int socketDescriptor) {
    PeerConnection::socketDescriptor = socketDescriptor;
}

void PeerConnection::setFileDescription(FileDescription *fileDescription) {
    PeerConnection::fileDescription = fileDescription;

}

PeerConnection::PeerConnection(FileDescription *fileDescription) {
    if (fileDescription != NULL)
        this->fileDescription = fileDescription;

}

void PeerConnection::start() {
    new std::thread([=] {_start();});
}
