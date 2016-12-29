//
// Created by alin on 12/29/16.
//

#include <cstring>
#include "Cacher.h"

std::vector<FileDescription> Cacher::loadFilesFromCache() {
    return std::vector<FileDescription>();
}

Cacher *Cacher::getInstance() {
    if (instance == NULL)
        instance = new Cacher();
    return instance;
}

Cacher::Cacher() {

}

void Cacher::registerNewFile(FileDescription fileDescription, const char *path) {
    std::string *spath = new std::string(path);
    filePaths.insert(std::make_pair(fileDescription,*spath));
    cacheFile(fileDescription,path);
    delete spath;

}

void Cacher::setServerIdentifier(Address address) {
    this->serverAddr = new Address(address);
}

const char *Cacher::getPathForFile(FileDescription fileDescription) {
    const char* path = filePaths.at(fileDescription).data();
    return path;
}

void Cacher::cacheFile(FileDescription fd,const char* file_path) {
    char path[100] = CACHE_LOCATION;
    std::string hash = fd.getHash();
    strcat(path, "/");
    strcat(path, hash.data());

    FILE* out = fopen(path,"w");
    fprintf(out,"%s\n",file_path);
    fprintf(out,"%s\n",fd.toString().data());
}

void Cacher::unregisterFile(FileDescription description) {
    char path[100] = CACHE_LOCATION;
    std::string hash = description.getHash();
    strcat(path, "/");
    strcat(path, hash.data());

    remove(path);
    filePaths.erase(description);
}
