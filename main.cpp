
#include <iostream>
#include "local/io/UserInteractor.h"
#include "local/storage/Cacher.h"
#include "network/ConnectionHandler.h"
#include "local/Publisher.h"


using namespace std;
int setup();
int main() {

    UserInteractor *userInteractor = UserInteractor::getInstance();
    int status = setup();
    while (status == -1)
    {
        status = setup();
    }

    userInteractor -> listenForCommands(); //this will listen to from the user;

    return 0;
}
int setup()
{
    UserInteractor *userInteractor = UserInteractor::getInstance();

    userInteractor->init();
    /**
    * TODO: think how to make userInteractor functions very extensible
    */
    Address *serverAddress;
    try {
        serverAddress = userInteractor->requestServerAddress();
    }
    catch(const char* ex)
    {
        printf("%s\n",ex);
        return -1;
    }

    Cacher *cacher = Cacher::getInstance();

    cacher->setServerIdentifier(*serverAddress);

    vector<FileDescription*> lastSessionFiles = cacher -> loadFilesFromCache();

    //TODO: integrity check here

    ConnectionHandler *connectionHandler;
    connectionHandler = ConnectionHandler::getInstance();

    if (connectionHandler -> connectToServer(*serverAddress) != -1) {
        //TODO : maybe try-catch
        connectionHandler -> startService();

        Publisher *publisher = new Publisher(connectionHandler->getServer());

        publisher->publish(lastSessionFiles); //on a new thread

        delete publisher;

        return 0;
    }

    return -1;

}