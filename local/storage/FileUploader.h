//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_FILEUPLOADER_H
#define CLIENT_FILEUPLOADER_H


#include "FileReader.h"
#define BLK_SIZE 4096
class FileUploader {
    FileReader *reader;
    int socket;
public:
    FileUploader(FileReader* reader,int socketDescrpitor);
    void upload();
};


#endif //CLIENT_FILEUPLOADER_H
