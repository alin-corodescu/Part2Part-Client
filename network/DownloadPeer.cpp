//
// Created by alin on 12/28/16.
//

#include <Command.h>
#include <cstring>
#include <cstdlib>
#include <CommandBuilder.h>
#include <IOWrappers.h>
#include "DownloadPeer.h"
#include "../local/storage/FileWriter.h"
#include "../local/storage/FileDownloader.h"


void DownloadPeer::request() {
    CommandBuilder commandBuilder;

    commandBuilder.setType(PROVIDE);
    commandBuilder.addArgument(fileDescription);
    Command request = commandBuilder.build();

    _sendCommand(request);
}

void DownloadPeer::listenForCommand() {
    char* command;

    command = readString(socketDescriptor,13);

    if (strcmp(command, commandName(TRANSFERRING)))
    {
        free(command);
        throw "Invalid command";
    }
    free(command);
}

void DownloadPeer::_start() {
    //as a downloader, you must make the request first
    //and then listen for TRANSFERRING
    request();
    try {
        listenForCommand();
    }
    catch (...){
        return;
    }


    downloadFile();
}

void DownloadPeer::downloadFile() {
    FileWriter *fileWriter = new FileWriter(dst,fileDescription);
    FileDownloader *fileDownloader = new FileDownloader(fileWriter,socketDescriptor);

    fileDownloader->download();
}
