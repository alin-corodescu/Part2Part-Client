//
// Created by alin on 12/21/16.
//
#pragma once
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
    Address* serverAddr;
    static Cacher* instance = NULL;
    std::map<FileDescription,std::string> filePaths;
    Cacher();
    void _removeFileNameFromPath(char *);
    /**
     * reads a cached file description and updates
     * the private members of the class
     */
    FileDescription readFileDescription(const char* path);
public:
    std::vector<FileDescription> loadFilesFromCache();

    void cacheFile(FileDescription,const char*);

    void setServerIdentifier(Address);

    // the publisher will need to publish this new file
    void registerNewFile(FileDescription fileDescription,const char* path,bool shouldCache = 1);

    void unregisterFile(FileDescription description);

    /**
     * returns the path of the file described
     * @param fileDescription
     */
    const char* getPathForFile(FileDescription fileDescription);

    static Cacher* getInstance();
};