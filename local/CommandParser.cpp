//
// Created by alin on 12/27/16.
//


#include <IOWrappers.h>
#include <FileDescription.h>
#include <vector>
#include "CommandParser.h"
#include <FileDescriptionBuilder.h>
#include "io/ResultsDisplayer.h"
#include "../network/PeerConnector.h"
#include "../network/ConnectionHandler.h"

FileDescription* CommandParser::readFileDescription() {
    FileDescriptionBuilder *fileDescriptionBuilder = new FileDescriptionBuilder();
    FileDescription *fileDescription;

    unsigned int fdSize;
    readUInt(socketDescriptor, fdSize);
    char *fileDescriptionString;

    fileDescriptionString = readString(socketDescriptor, fdSize);
    fileDescription = fileDescriptionBuilder->buildFromString(fileDescriptionString);
    free(fileDescriptionString);

    delete fileDescriptionBuilder;
    return fileDescription;
}

void CommandParser::parseResults() {
    unsigned int number_of_matches;
    unsigned int i;
    std::vector<FileDescription*> results;

    FileDescriptionBuilder fileDescriptionBuilder;
    readUInt(socketDescriptor, number_of_matches);

    for (i = 0; i < number_of_matches; i++) {

        FileDescription *fileDescription;

        fileDescription = readFileDescription();

        results.push_back(fileDescription);

    }

    //pass the results to the results displayer

    ResultsDisplayer* resultsDisplayer = ResultsDisplayer::getInstance();

    resultsDisplayer->display(results);

}

void CommandParser::parseRequestFileFrom() {
    FileDescription* fileDescription = readFileDescription();
    unsigned int i;
    unsigned int numberOfPeers;
    std::vector<Address> addresses;
    readUInt(socketDescriptor, numberOfPeers);
    for (i = 0; i < numberOfPeers; i++) {
        //12 bytes per adress pair public - private
        unsigned int publicIP, privateIP;
        unsigned short publicPort, privatePort;
        readUInt(socketDescriptor, publicIP);
        readUShort(socketDescriptor, publicPort);
        readUInt(socketDescriptor, privateIP);
        readUShort(socketDescriptor, privatePort);

        Address *a = new Address(publicIP, publicPort,
                                 privateIP, privatePort);

        addresses.push_back(*a);
        delete (a);
    }

    PeerConnector *peerConnector = new PeerConnector(fileDescription, addresses);

    peerConnector->start();
}

void CommandParser::parseOpenCommand() {
    unsigned int ip_addr;
    unsigned short port;
    readUInt(socketDescriptor, ip_addr);
    readUShort(socketDescriptor, port);

    Address a(ip_addr, port);

    ConnectionHandler::getInstance()->acceptNATTraversal(a);
}

CommandParser::CommandParser(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;

}
