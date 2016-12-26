//
// Created by alin on 12/21/16.
//

#include <queue>
#include "../local/Command.h"

#ifndef CLIENT_SERVER_H
#define CLIENT_SERVER_H

#endif //CLIENT_SERVER_H

class Server
{
private:
    int _socketDescriptor;
    std::queue<Command> commandQueue;
    /**
     * function used to send the command
     * to the server
     * NOTE: will NOT release the lock
     * until it receives the confirmation (TBD)
     */
    void _executeCommand();
    /**
     * function used to pop Commands from the
     * queue and send them to the server
     */
    void _processCommandQueue();


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
     */
    void listenForCommands();
};