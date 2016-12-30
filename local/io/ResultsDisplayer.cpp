//
// Created by alin on 12/21/16.
//

#include "ResultsDisplayer.h"

void ResultsDisplayer::display(std::vector<FileDescription> fds) {

    int i;
    indexMap.clear();
    for (i = 0; i < fds.size(); i++)
    {
        indexMap.insert(std::make_pair(i,fds[i]));

        printf("1 : \n");
        printf("\tName: %s\n",fds[i].getFileName());
    }
}

FileDescription ResultsDisplayer::getFDForIndex(int index) {
    return indexMap.at(index);
}
