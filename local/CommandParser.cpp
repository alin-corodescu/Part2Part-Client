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
#include "../network/Address.h"
#include "../network/PeerConnector.h"
#include "../network/PeerConnection.h"

FileDescription CommandParser::readFileDescription()
{
    FileDescriptionBuilder fileDescriptionBuilder;
    FileDescription fileDescription;

    unsigned int fdSize;
    readUInt(socketDescriptor,fdSize);
    char* fileDescriptionString;
    readUInt(socketDescriptor,fdSize);

    fileDescriptionString = readString(socketDescriptor,fdSize);
    fileDescription = fileDescriptionBuilder.buildFromString(fileDescriptionString);
    free(fileDescriptionString);

    return fileDescription;
}
void CommandParser::parseResults() {
    unsigned int number_of_matches;
    unsigned int i;
    std::vector<FileDescription> results;

    FileDescriptionBuilder fileDescriptionBuilder;
    readUInt(socketDescriptor,number_of_matches);

    for (i =0; i < number_of_matches; i++)
    {

        FileDescription fileDescription;

        fileDescription = readFileDescription();

        results.push_back(fileDescription);

    }

    //pass the results to the results displayer

    ResultsDisplayer resultsDisplayer;

    resultsDisplayer.display(results);

}

void CommandParser::parseRequestFileFrom() {
    FileDescription fileDescription = readFileDescription();
    unsigned int i;
    unsigned int numberOfPeers;
    std::vector<Address> addresses;
    readUInt(socketDescriptor,numberOfPeers);
    for (i = 0; i < numberOfPeers; i++)
    {
        //12 bytes per adress pair public - private
        unsigned int publicIP,privateIP;
        unsigned short publicPort,privatePort;
        readUInt(socketDescriptor,publicIP);
        readUShort(socketDescriptor,publicPort);
        readUInt(socketDescriptor,privateIP);
        readUShort(socketDescriptor,privatePort);

        Address *a = new Address(publicIP,publicPort,
                                    privateIP,privatePort);

        addresses.push_back(*a);
        delete(a);
    }

    PeerConnector *peerConnector = new PeerConnector(fileDescription,addresses);

    peerConnector->start();

}