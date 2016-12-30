//
// Created by alin on 12/29/16.
//

#include <cstring>
#include <dirent.h>
#include "Cacher.h"

Cacher* Cacher::instance = NULL;

std::vector<FileDescription> Cacher::loadFilesFromCache() {
    std::vector<FileDescription> files;
    char path[100] = CACHE_LOCATION;
    strcat(path,"/");

    DIR* d;
    d = opendir(CACHE_LOCATION);

    dirent* element = readdir(d);
    while (element)
    {
        if (!strcmp(element->d_name,".")  || !strcmp(element->d_name,"..")) {
            _removeFileNameFromPath(path);
            strcat(path,element->d_name);
            FileDescription fileDescription = readFileDescription(path);
            files.push_back(fileDescription);

            registerNewFile(fileDescription,path,false);
        }
        element = readdir(d);
    }

    return files;
}

Cacher *Cacher::getInstance() {
    if (instance == NULL)
        instance = new Cacher();
    return instance;
}

Cacher::Cacher() {

}

void Cacher::registerNewFile(FileDescription fileDescription, const char *path,bool shouldCache) {
    std::string *spath = new std::string(path);
    filePaths.insert(std::make_pair(fileDescription,*spath));
    if (shouldCache) cacheFile(fileDescription,path);
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

void Cacher::_removeFileNameFromPath(char * path) {
    int lg = strlen(path);
    int i = lg - 1;
    while ( i >= 0 )
    {
        if (path[i] =='/') break;
    }

}
