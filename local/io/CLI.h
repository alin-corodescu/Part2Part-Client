//
// Created by alin on 12/26/16.
//

#ifndef CLIENT_CLI_H
#define CLIENT_CLI_H


#include "UserInteractor.h"
/**
 * implementation of a Command Line Interface
 * mostly simplist, with little error-checking
 * for debugging purposes mainly
 */
class CLI : public UserInteractor {
private:
    void processQuery();
    void processChose();
    void showHelp();
    void processPublishRequest();
    void processUnpublishRequest();
    void proccessDisconnectRequest();

public:
    virtual void init() override;

    virtual void listenForCommands() override;

    /**
     * Requests a server address from the user
     * @return a pointer to Address structure, programmer should call delete
     * on it when no longer needed
     */
    virtual Address* requestServerAddress() override;
};


#endif //CLIENT_CLI_H
