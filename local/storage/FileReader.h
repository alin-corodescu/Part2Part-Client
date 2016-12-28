//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_FILEREADER_H
#define CLIENT_FILEREADER_H


#include <FileDescription.h>
#include <istream>

class FileReader {
    char* path;
    FileDescription fileDescription;
    std::istream* in;
public:
    FileReader(char* path,FileDescription fileDescription);
    /**
     * reads next chunk of the file,
     * @param buffer
     * @return - the number of bytes read
     */
    unsigned int nextBlock(char* buffer);
    void finish();
};


#endif //CLIENT_FILEREADER_H
