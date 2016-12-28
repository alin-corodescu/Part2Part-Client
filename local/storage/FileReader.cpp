//
// Created by alin on 12/21/16.
//

#include "FileReader.h"

FileReader::FileReader(char *path, FileDescription fileDescription) {
    this ->path = path;
    this->fileDescription = fileDescription;

}

unsigned int FileReader::nextBlock(char *buffer) {
    return 0;
}
