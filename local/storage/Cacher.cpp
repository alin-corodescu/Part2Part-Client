//
// Created by alin on 12/29/16.
//

#include <cstring>
#include <dirent.h>
#include <IntegrityChecker.h>
#include "Cacher.h"
#include "../FileDescriptionBuilder.h"

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
            strcat(path, element->d_name);
            FileDescription* fileDescription;
            try {
                fileDescription = new FileDescription(readFileDescription(path));
                files.push_back(*fileDescription);
                delete fileDescription;
            }
            catch (...)
            {
                element = readdir(d);
                continue;
            }



            //registerNewFile(fileDescription,path,false);
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

FileDescription Cacher::readFileDescription(const char *path) {
    FILE* in = fopen(path,"r");

    char *buffer;
    size_t pathLength;

    getline(&buffer,&pathLength,in);

    char* pathToFile = (char*) malloc(pathLength);
    strcpy(pathToFile,buffer);
    free(buffer);

    if (pathToFile[pathLength-1] == '\n')
        pathToFile[--pathLength] = '\0';

    FileDescriptionBuilder *builder = new FileDescriptionBuilder();
    FileDescription fileDescription = builder->readFromFile(in);

    delete builder;
    if (IntegrityChecker::checkIntegrity(fileDescription,pathToFile))
        registerNewFile(fileDescription,pathToFile,0);
    else
        throw;

    free(pathToFile);

}
