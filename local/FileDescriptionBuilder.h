//
// Created by alin on 12/21/16.
//
#pragma once
#ifndef CLIENT_FILEDESCRIPTIONBUILDER_H
#define CLIENT_FILEDESCRIPTIONBUILDER_H


#include <FileDescription.h>

class FileDescriptionBuilder {
public:
    FileDescription buildFromString(char* string);
    FileDescription readFromFile(FILE* file);
};


#endif //CLIENT_FILEDESCRIPTIONBUILDER_H
