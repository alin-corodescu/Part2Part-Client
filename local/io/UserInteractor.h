//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_INPUTREQUESTER_H
#define CLIENT_INPUTREQUESTER_H

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
};


#endif //CLIENT_INPUTREQUESTER_H
