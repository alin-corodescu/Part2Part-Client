//
// Created by alin on 12/21/16.
//

#include <FileDescription.h>
#include <vector>
#include <map>
#include "../../network/Address.h"

#ifndef CLIENT_CACHER_H
#define CLIENT_CACHER_H
#endif //CLIENT_CACHER_H
#define CACHE_LOCATION ".cache"
class Cacher
{
private:
    std::map<std::string,FileDescription> filePaths;
public:
    std::vector<FileDescription> loadFilesFromCache();

    void cacheFile(FileDescription);

    void setServerIdentifier(Address);

    // the publisher will need to publish this new file
    void registerNewFile(FileDescription fileDescription,const char* path);

    /**
     * returns the path of the file described
     * @param fileDescription
     */
    char* getPathForFile(FileDescription fileDescription);

    static Cacher* getInstance();
};