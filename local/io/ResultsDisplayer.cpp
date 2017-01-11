//
// Created by alin on 12/21/16.
//

#include "ResultsDisplayer.h"


ResultsDisplayer* ResultsDisplayer::instance;

void ResultsDisplayer::display(std::vector<FileDescription*> fds) {

    int i;
    indexMap.clear();
    for (i = 0; i < fds.size(); i++)
    {
        indexMap.insert(std::make_pair(i + 1,fds[i]));

        printf("1 : \n");
        printf("\tName: %s\n",fds[i]->getFileName().data());
    }
}

FileDescription* ResultsDisplayer::getFDForIndex(int index) {
    FileDescription* fileDescription =  indexMap.find(index)->second;
    return fileDescription;
}

ResultsDisplayer *ResultsDisplayer::getInstance() {
    if (instance == NULL)
        instance = new ResultsDisplayer();
    return instance;
}
