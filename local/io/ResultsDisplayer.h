//
// Created by alin on 12/21/16.
//
#pragma once
#ifndef CLIENT_RESULTSDISPLAYER_H
#define CLIENT_RESULTSDISPLAYER_H


#include <FileDescription.h>
#include <vector>
#include <map>

class ResultsDisplayer {
private:
    static ResultsDisplayer* instance;
    std::map<int,FileDescription*> indexMap;
public:
    void display(std::vector<FileDescription*>);
    FileDescription* getFDForIndex(int index);
    static ResultsDisplayer* getInstance();
};


#endif //CLIENT_RESULTSDISPLAYER_H
