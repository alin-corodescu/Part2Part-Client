//
// Created by alin on 12/21/16.
//
#pragma once
#ifndef CLIENT_INPUTREQUESTER_H
#define CLIENT_INPUTREQUESTER_H

#include <Address.h>
#include "ResultsDisplayer.h"

/**
 * interface provided to communicate
 * with the end-user, implementations
 * will differ from CLI to GUI
 */

#define CMD 1
#define GUI 2
class UserInteractor {
    friend class CLI;
private:
    static UserInteractor* instance;
public:
    static const int type = CMD;
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
