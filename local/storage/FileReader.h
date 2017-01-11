//
// Created by alin on 12/21/16.
//
#pragma once
#ifndef CLIENT_FILEREADER_H
#define CLIENT_FILEREADER_H


#include <FileDescription.h>
#include <istream>
#include <fstream>

class FileReader {
    const char* path;
    FileDescription* fileDescription;
    std::ifstream in;
public:
    FileReader(const char* path,FileDescription* fileDescription);
    /**
     * reads next chunk of the file,
     * @param buffer
     * @return - the number of bytes read
     */
    unsigned int nextBlock(char* buffer);
    void finish();
};


#endif //CLIENT_FILEREADER_H
