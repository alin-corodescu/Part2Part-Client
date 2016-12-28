//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_FILEWRITER_H
#define CLIENT_FILEWRITER_H


#include <FileDescription.h>
#include <fstream>

class FileWriter {
    char* path;
    FileDescription fileDescription;
    std::ofstream* file;
public:
    FileWriter(const char* path, FileDescription fileDescription);
    void createEmptyFile();
    void append(const char* buffer,int count);
    void finish();
};


#endif //CLIENT_FILEWRITER_H
