#include <iostream>
#include "local/io/UserInteractor.h"
#include "local/storage/Cacher.h"

using namespace std;
void setup(const UserInteractor& userInteractor,Cacher*& cacher);
int main() {

    UserInteractor *userInteractor;
    Cacher *cacher;

    userInteractor -> init(); //initialize the user interface




    return 0;
}
void setup(const UserInteractor& userInteractor,Cacher*& cacher)
{

    /**
    * TODO: think how to make userInteractor functions very extensible
    */
    Address serverAddress = userInteractor.requestServerAddress();

    cacher = NULL; //TODO: actual instance, with the server address

    vector<FileDescription> lastSessionFiles = cacher -> loadFilesFromCache();

    //TODO: integrity check here

    
}