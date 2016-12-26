//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_INPUTREQUESTER_H
#define CLIENT_INPUTREQUESTER_H

#include "../../network/Address.h"

/**
 * interface provided to communicate
 * with the end-user, implementations
 * will differ from CLI to GUI
 */
class UserInteractor {
public:
    /**
     * function used to build the GUI, and prepare
     * to capture and request user input.
     */
    virtual void init() = 0;

    /**
     * will operate on the main thread,
     * listening for user input
     */
    virtual void listenForCommands() = 0;

    virtual Address* requestServerAddress() = 0;

    static UserInteractor* getInstance();
};


#endif //CLIENT_INPUTREQUESTER_H
