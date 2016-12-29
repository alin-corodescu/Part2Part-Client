//
// Created by alin on 12/28/16.
//

#include <IOWrappers.h>
#include <cstring>
#include <Command.h>
#include <cstdlib>
#include <CommandBuilder.h>
#include "UploadPeer.h"
#include "../local/FileDescriptionBuilder.h"
#include "../local/storage/Cacher.h"
#include "../local/storage/FileUploader.h"
#include "../local/storage/FileReader.h"

void UploadPeer::listenForCommand() {
    char* command;

    command = readString(socketDescriptor,13);

    if (strcmp(command, commandName(PROVIDE)))
    {
        free(command);
        throw "Invalid command";
    }
    unsigned int size;
    readUInt(socketDescriptor,size);
    char* fdString;

    fdString = readString(socketDescriptor,size);
    FileDescriptionBuilder fileDescriptionBuilder;

    fileDescription = fileDescriptionBuilder.buildFromString(fdString);
    free(fdString);

    Cacher *cacher = Cacher::getInstance();
    path = cacher->getPathForFile(fileDescription);
    free(command);
}

int UploadPeer::_start() {
    try {
        listenForCommand();
        uploadFile();
        return 0;
    }
    catch(...)
    {
        return -1;
    }
}

void UploadPeer::uploadFile() {
    //i have path, and file Description loaded.
    int size = fileDescription.getFileSize();

    CommandBuilder commandBuilder;
    commandBuilder.setType(TRANSFERRING);
    commandBuilder.addArgument(size);

    Command transfer = commandBuilder.build();

    _sendCommand(transfer);

    FileReader *reader = new FileReader(path,fileDescription);
    FileUploader *uploader = new FileUploader(reader,socketDescriptor);

    uploader->upload();

}

UploadPeer::UploadPeer(int socket) {
    this->setSocketDescriptor(socket);

}
