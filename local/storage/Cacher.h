//
// Created by alin on 12/21/16.
//

#include <FileDescription.h>
#include <vector>
#include "../../network/Address.h"

#ifndef CLIENT_CACHER_H
#define CLIENT_CACHER_H
#endif //CLIENT_CACHER_H
#define CACHE_LOCATION ".cache"
class Cacher
{
public:
    virtual std::vector<FileDescription> loadFilesFromCache() = 0;

    virtual void cacheFile(FileDescription) = 0;

    virtual void setServerIdentifier(Address) = 0;

    // the publisher will need to publish this new file
    virtual void registerNewFile(FileDescription fileDescription,const char* path);

    /**
     * returns the path of the file described
     * @param fileDescription
     */
    virtual char* getPathForFile(FileDescription fileDescription);

    static Cacher* getInstance();
};