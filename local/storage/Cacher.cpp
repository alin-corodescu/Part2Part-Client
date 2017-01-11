//
// Created by alin on 12/29/16.
//

#include <cstring>
#include <dirent.h>
#include <IntegrityChecker.h>
#include "Cacher.h"
#include <FileDescriptionBuilder.h>

Cacher* Cacher::instance = NULL;

std::vector<FileDescription*> Cacher::loadFilesFromCache() {
    std::vector<FileDescription*> files;
    char path[100] = CACHE_LOCATION;
    strcat(path,"/");
    DIR* d;
    d = opendir(CACHE_LOCATION);
    if (d != NULL) {
        dirent *element = readdir(d);
        while (element) {
            if (strcmp(element->d_name, ".") && strcmp(element->d_name, "..")) {
                _removeFileNameFromPath(path);
                strcat(path, element->d_name);
                FileDescription *fileDescription;
                try {
                    fileDescription = readFileDescription(path);
                    files.push_back(fileDescription);
                    //delete fileDescription;
                }
                catch (...) {
                    element = readdir(d);
                    continue;
                }



                //registerNewFile(fileDescription,path,false);
            }
            element = readdir(d);
        }

        return files;
    }
}

Cacher *Cacher::getInstance() {
    if (instance == NULL)
        instance = new Cacher();
    return instance;
}

Cacher::Cacher() {

}

void Cacher::registerNewFile(FileDescription *fileDescription, const char *path,bool shouldCache) {
    std::string *spath = new std::string(path);
    filePaths.insert(std::make_pair(*fileDescription,*spath));
    if (shouldCache) cacheFile(fileDescription,path);
    delete spath;

}

void Cacher::setServerIdentifier(Address address) {
    this->serverAddr = new Address(address);
}

const char *Cacher::getPathForFile(FileDescription *fileDescription) {
    const char* path = filePaths.at(*fileDescription).data();
    return path;
}

void Cacher::cacheFile(FileDescription* fd,const char* file_path) {
    char path[100] = CACHE_LOCATION;
    std::string hash = fd->getHash();
    strcat(path, "/");
    strcat(path, hash.data());

    FILE* out = fopen(path,"w");
    int rc = fprintf(out,"%s\n",file_path);
    fprintf(out,"%s",fd->toString().data());
    fflush(out);
    fclose(out);
}

void Cacher::unregisterFile(FileDescription* description) {
    char path[100] = CACHE_LOCATION;
    std::string hash = description->getHash();
    strcat(path, "/");
    strcat(path, hash.data());

    remove(path);
    filePaths.erase(*description);
}

void Cacher::_removeFileNameFromPath(char * path) {
    int lg = strlen(path);
    int i = lg - 1;
    while ( i >= 0 )
    {
        if (path[i] =='/') break;
    }

}

FileDescription* Cacher::readFileDescription(const char *path) {
    FILE* in = fopen(path,"r");

    char *buffer = NULL;
    size_t pathMaxLength = 255;

    getline(&buffer,&pathMaxLength,in);

    char* pathToFile = (char*) malloc(strlen(buffer));
    strcpy(pathToFile,buffer);
    free(buffer);
    int pathLength = strlen(pathToFile);
    if (pathToFile[pathLength- 1] == '\n')
        pathToFile[pathLength - 1] = '\0';

    /*long size = ftell(in);
    int rc = fseek(in,0,SEEK_END);
    long size2 = ftell(in);*/

    FileDescriptionBuilder builder;
    FileDescription *fileDescription = builder.readFromFile(in);


    if (IntegrityChecker::checkIntegrity(*fileDescription,pathToFile))
        registerNewFile(fileDescription,pathToFile,0);
    else
        throw;

    free(pathToFile);

    return fileDescription;
}
