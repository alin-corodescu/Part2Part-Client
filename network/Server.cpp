//
// Created by alin on 12/26/16.
//

#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include "Server.h"
#include "Command.h"
#include "IOWrappers.h"


void Server::_listenForCommands() {
    /**
     * commands will be parsed on the thread of this function
     * as another command cannot be processed until the whole data
     * of the previous one has been processed
     */
    char* command;
    while (1)
    {
        //read(_socketDescriptor, command, 13);

        command = readString(_socketDescriptor,13);

        if (!strcmp(command, commandName(RESULTS))) {
            incomingCommandParser.parseResults();
        }

        if (!strcmp(command, commandName(REQUEST))) {
            incomingCommandParser.parseRequestFileFrom();
        }

        if (!strcmp(command, commandName(OPEN))) {
            incomingCommandParser.parseOpenCommand();
        }

        free(command);

    }
}
