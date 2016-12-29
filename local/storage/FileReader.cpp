//
// Created by alin on 12/21/16.
//

#include "FileReader.h"
#include "FileUploader.h"

FileReader::FileReader(const char *path, FileDescription fileDescription) {
    this ->path = path;
    this->fileDescription = fileDescription;
    in = new std::istream(path,std::ios::in | std::ios::binary);

}

unsigned int FileReader::nextBlock(char *buffer) {

    in->read(buffer,BLK_SIZE);
    //check here for other errors (other than eof or shit);
    if (!in)
    {
        long count = in->gcount();
        in->clear();
        return count;
    }
    return BLK_SIZE;
}

void FileReader::finish() {
    delete in;
}
