//
// Created by alin on 12/26/16.
//
#pragma once
#include <cstdio>
#include <cstring>
#include <string>
#include <FileDescription.h>

using namespace std;
#include "CLI.h"
#include "../QueryExecutor.h"
#include "CommandBuilder.h"
#include "../../network/ConnectionHandler.h"

void CLI::init() {
    printf("Welcome to Part2Part!\n");
}

void CLI::listenForCommands() {
    char command[50];
    while(1)
    {
        scanf("%s", command);
        if (!strcmp(command,"query"))
            processQuery();
        else if (!strcmp(command,"chose"))
            processChose();
        else if (!strcmp(command,"help"))
            showHelp();
        else if (!strcmp(command,"publish"))
            processPublishRequest();
        else if (!strcmp(command,"unpublish"))
            processUnpublishRequest();
        else if (!strcmp(command,"disconnect"))
            proccessDisconnectRequest();
        else
            printf("Invalid command. Try \"help\" for suggestions\n");

    }
}

Address* CLI::requestServerAddress() {
    static Address* address;
    char stringAddr[22];
    printf("Please specify the IP and the port of the server (IP:PORT) : \n");

    scanf("%s",stringAddr);

    address = new Address(stringAddr);

    return address;
}

void CLI::processQuery() {
    char name[50];
    int fileSize;
    char **desc, **type; size_t descSize = 0, typeSize = 0;

    printf("Name of the file to be searched:\n");
    scanf("%s", name);

    printf("Description of the file [optional]:\n");
    getline(desc,&descSize,stdin);

    printf("Type of the file [optional]: \n");
    getline(type, &typeSize, stdin);

    printf("Size of the file [0=default]: \n");
    scanf("%d",&fileSize);

    FileDescription *query;
    QueryExecutor *executor = new QueryExecutor(*query);
    executor->execute();

}

void CLI::processChose() {

    int index;
    ResultsDisplayer resultsDisplayer;
    scanf("%d",&index);
    FileDescription *fileDescription;
    try {
        *fileDescription = resultsDisplayer.getFDForIndex(index);
    }
    catch (exception& e){
        printf("Please try another index\n");
    }

    CommandBuilder commandBuilder;

    commandBuilder.setType(CommandTypes::FIND);

    commandBuilder.addArgument(fileDescription);

    Command command = commandBuilder.build();

    auto connectionHandler = ConnectionHandler::getInstance();

    connectionHandler->getServer().executeCommand(command);

}

CLI::CLI() {


}
