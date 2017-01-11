//
// Created by alin on 12/21/16.
//

#include <IOWrappers.h>
#include "FileDownloader.h"
#include "Cacher.h"

FileDownloader::FileDownloader(FileWriter *fileWriter, int socketDescriptor) {
    this ->fileWriter = fileWriter;
    this-> socketDescriptor =socketDescriptor;
}

void FileDownloader::download() {
    char* buffer;
    unsigned int size;
    unsigned int done = 0;


    fileWriter->createEmptyFile();
    readUInt(socketDescriptor,size);
    while (done < size) //while it's not done yet
    {
        unsigned int next_block;
        next_block = BLK_SIZE;
        if (size - done < BLK_SIZE)
            next_block = size - done;
        buffer = readString(socketDescriptor,next_block);
        fileWriter -> append(buffer, next_block);
        done += next_block;
    }
    printf("Downloaded %d bytes\n",size);
    fileWriter->finish();
    delete fileWriter;

}
