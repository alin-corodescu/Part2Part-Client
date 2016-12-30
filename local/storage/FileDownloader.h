//
// Created by alin on 12/21/16.
//
#pragma once
#ifndef CLIENT_FILEDOWNLOADER_H
#define CLIENT_FILEDOWNLOADER_H


#include "FileWriter.h"
#define BLK_SIZE 4096
class FileDownloader {
private:
    FileWriter* fileWriter;
    int socketDescriptor;
public:
    FileDownloader(FileWriter* fileWriter,int socketDescriptor);
    void download();
};


#endif //CLIENT_FILEDOWNLOADER_H
