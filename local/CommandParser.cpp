//
// Created by alin on 12/27/16.
//

#include <unistd.h>
#include <netinet/in.h>
#include <IOWrappers.h>
#include <FileDescription.h>
#include <vector>
#include "CommandParser.h"
#include "FileDescriptionBuilder.h"
#include "io/ResultsDisplayer.h"


void CommandParser::parseResults() {
    unsigned int number_of_matches;
    unsigned int i;
    std::vector<FileDescription> results;

    FileDescriptionBuilder fileDescriptionBuilder;
    readUInt(socketDescriptor,number_of_matches);

    for (i =0; i < number_of_matches; i++)
    {
        //begin parsing a new FileDescrption
        unsigned int size;
        char* fileDescriptionString;
        readUInt(socketDescriptor,size);

        fileDescriptionString = readString(socketDescriptor,size);

        FileDescription fileDescription;

        fileDescription = fileDescriptionBuilder.buildFromString(fileDescriptionString);

        results.push_back(fileDescription);
    }

    //pass the results to the results displayer

    ResultsDisplayer resultsDisplayer;

    resultsDisplayer.display(results);

}