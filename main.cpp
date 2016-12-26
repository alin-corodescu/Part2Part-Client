#include <iostream>
#include "local/io/UserInteractor.h"
#include "local/storage/Cacher.h"
#include "network/ConnectionHandler.h"
#include "local/Publisher.h"


using namespace std;
void setup();
int main() {

    UserInteractor *userInteractor = UserInteractor::getInstance();
    setup();

    userInteractor -> listenForCommands(); //this will listen to from the user;

    return 0;
}
void setup()
{
    UserInteractor *userInteractor = UserInteractor::getInstance();

    userInteractor->init();
    /**
    * TODO: think how to make userInteractor functions very extensible
    */
    Address *serverAddress = userInteractor -> requestServerAddress();

    Cacher *cacher = Cacher::getInstance();

    cacher->setServerIdentifier(*serverAddress);

    vector<FileDescription> lastSessionFiles = cacher -> loadFilesFromCache();

    //TODO: integrity check here

    ConnectionHandler *connectionHandler;
    connectionHandler = ConnectionHandler::getInstance();

    //TODO : maybe try-catch
    connectionHandler -> connectToServer(*serverAddress);

    Publisher *publisher = new Publisher(connectionHandler->getServer());

    publisher->publish(lastSessionFiles); //on a new thread

}