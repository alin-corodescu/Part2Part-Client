//
// Created by alin on 12/21/16.
//
#pragma once
#include <queue>
#include <IOWrappers.h>
#include <mutex>
#include "Command.h"
#include "../local/CommandParser.h"
#include <Address.h>

#ifndef CLIENT_SERVER_H
#define CLIENT_SERVER_H

#endif //CLIENT_SERVER_H
#define HEARTBEAT_INTERVAL 5
class Server
{ friend class NATTraversalUtils;
    friend class ConnectionHandler;
private:
    static std::mutex clockMutex;
    static std::mutex qMutex;
    std::chrono::steady_clock::time_point last_command;
    Address address;
    CommandParser incomingCommandParser;
    int _socketDescriptor;
    bool connected;
    std::queue<Command> commandQueue;
    void _hearbeats();
protected:
    /**
     * function used to send the command
     * to the server
     * NOTE: will NOT release the lock
     * until it receives the confirmation (TBD)
     */
    void _executeCommand(Command command);
    /**
     * function used to pop Commands from the
     * queue and send them to the server
     */
    void _processCommandQueue();

    void _listenForCommands();

    /**
     * waits to receive an open command from
     * the server, useful in the case of NAT traversing
     * @returns the address argument of the open command
     */
    Address listenForOpen();


public:
    /**
     * function which will queue all the commands
     * to reduce thread concurrency problems
     * @param command
     */
    void executeCommand(Command command);

    /**
     * start-up function for the server,
     * on it's own thread, listens for responses
     * and commands from the server
     * @tag own thread
     */
    void listenForCommands();

    Address getAddress();

    Server(int socket,Address serverAddress);

    int getPublicIP();
    /**
     * starts a new thread to process
     * commands
     */
    void processCommandQueue();

    /**
     * sends at regular time intervals, if no other command
     * has been sent, a heartbeat.
     */
    void heartbeats();
    /**
     * Copy constructor
     */
    Server(const Server& s);
};



