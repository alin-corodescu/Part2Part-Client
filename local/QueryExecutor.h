//
// Created by alin on 12/26/16.
//

#ifndef CLIENT_QUERYEXECUTOR_H
#define CLIENT_QUERYEXECUTOR_H

#include <FileDescription.h>

/**
 * class responsible with the execution
 * of queries.
 */
class QueryExecutor {
private:
    FileDescription *query;
public:
    QueryExecutor(FileDescription query);

    void execute();
};


#endif //CLIENT_QUERYEXECUTOR_H
