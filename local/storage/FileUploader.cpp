//
// Created by alin on 12/21/16.
//

#include <cstdlib>
#include <IOWrappers.h>
#include "FileUploader.h"

FileUploader::FileUploader(FileReader *reader, int socketDescrpitor) {
    this->reader =reader;
    this->socket = socketDescrpitor;
}

void FileUploader::upload() {

    char *buffer;
    unsigned int count = 0;

    buffer = (char *) malloc(BLK_SIZE);
    do
    {
        count = reader->nextBlock(buffer);
        writeString(socket,buffer,count);
    }
    while (count);


}
