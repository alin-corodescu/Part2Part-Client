//
// Created by alin on 12/26/16.
//
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <CommandBuilder.h>
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

        command = readString(_socketDescriptor,COMM_LENGTH);

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
int Server::getPublicIP() {
    unsigned int ip;
    free(readString(_socketDescriptor,COMM_LENGTH));
    readUInt(_socketDescriptor,ip);
    return ip;
}

void Server::_processCommandQueue() {
    while (connected)
    {
        queueLock.lock();
        bool isEmpty = commandQueue.empty();
        queueLock.unlock();
        while (!isEmpty)
        {
            queueLock.lock();
            Command next = commandQueue.front();
            commandQueue.pop();
            queueLock.unlock();

            _executeCommand(next);
            queueLock.lock();
            isEmpty = commandQueue.empty();
            queueLock.unlock();
        }
    }
}

Server::Server(int socket,Address serverAddress) : address(serverAddress), incomingCommandParser(socket) {
    this->_socketDescriptor = socket;
}

void Server::_executeCommand(Command command) {
    int size;
    size = command.length();
    char *string = (char*) malloc(size);
    command.toString(string);
    writeString(_socketDescriptor,string, size);
    free(string);
    clockLock.lock();
    //mark the time it sent the command
    last_command = std::chrono::steady_clock::now();
    clockLock.unlock();

}

Address Server::listenForOpen() {
    char* cmd;

    cmd = readString(_socketDescriptor,COMM_LENGTH);
    if (!strcmp(cmd,"OPEN"))
    {
        unsigned int  ip;
        readUInt(_socketDescriptor, ip);
        unsigned short port;
        readUShort(_socketDescriptor,port);
        return Address(ip,port);
    }
    else {
        throw "Invalid command received";
    }
}

Address Server::getAddress() {
    return address;
}

void Server::processCommandQueue() {
    //start a new thread with _processCommandQueue

    std::thread([=] {_processCommandQueue();});

}

void Server::executeCommand(Command command) {
    queueLock.lock();
    commandQueue.push(command);
    queueLock.unlock();
}

void Server::listenForCommands() {
    std::thread([=] {_listenForCommands();});
}

Server::Server(const Server &s) : address(s.address), incomingCommandParser(s.incomingCommandParser) {
    _socketDescriptor = s._socketDescriptor;
    connected = s.connected;
}

void Server::heartbeats() {
    std::thread([=] {_hearbeats();});
}

void Server::_hearbeats() {
    using namespace std::chrono;
    while (connected) {
        clockLock.lock();
        steady_clock::time_point now = steady_clock::now();
        duration<double> timeElpased = duration_cast<duration<double>>(now - last_command);
        if (timeElpased.count() > HEARTBEAT_INTERVAL) {
            CommandBuilder *commandBuilder = new CommandBuilder();
            commandBuilder->setType(HEARTBEAT);
            Command heartbeat = commandBuilder->build();
            executeCommand(heartbeat);
            delete commandBuilder;
            last_command = steady_clock::now();
        }
        clockLock.unlock();
    }
}
