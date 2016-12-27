//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_RESULTSDISPLAYER_H
#define CLIENT_RESULTSDISPLAYER_H


#include <FileDescription.h>
#include <vector>
#include <map>

class ResultsDisplayer {
private:
    std::map<int,FileDescription> indexMap;
public:
    void display(std::vector<FileDescription>);
    FileDescription getFDForIndex(int index);
};


#endif //CLIENT_RESULTSDISPLAYER_H
