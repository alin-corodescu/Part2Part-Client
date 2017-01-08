//
// Created by alin on 12/26/16.
//
#include <cstdio>
#include <cstring>
#include <string>
#include <FileDescription.h>
#include <FileDescriptionBuilder.h>
#include <sys/stat.h>
#include <IntegrityChecker.h>

using namespace std;
#include "CLI.h"
#include "../QueryExecutor.h"
#include "CommandBuilder.h"
#include "../../network/ConnectionHandler.h"
#include "../Publisher.h"

void CLI::init() {
    printf("Welcome to Part2Part!\n");
}

void CLI::listenForCommands() {
    char command[50];
    while(1)
    {
        printf("Command: ");
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

        printf("\n");

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
    char *desc = NULL, *type = NULL; size_t descSize = 0, typeSize = 0;

    printf("Name of the file to be searched:\n");
    scanf("%s", name);

    printf("Description of the file [optional]:\n");
    getline(&desc,&descSize,stdin);

    printf("Type of the file [optional]: \n");
    getline(&type, &typeSize, stdin);

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
        fileDescription = new FileDescription(resultsDisplayer.getFDForIndex(index));
    }
    catch (exception& e){
        printf("Please try another index\n");
        return;
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

void CLI::showHelp() {

}

void CLI::processPublishRequest() {
#define DESC_LEGNTH 500
    FileDescription* fileDescription;
    FileDescriptionBuilder * builder = new FileDescriptionBuilder();
    char * path = NULL;
    struct stat buffer;
    size_t pathLength;
    printf("Path to the file: \n");
    getline(&path,&pathLength,stdin);
    if (!stat(path,&buffer)) {
        if (S_ISREG(buffer.st_mode)) {
            char * name = basename(path);
            builder->init();
            builder->addSize(buffer.st_size);
            builder->addName(name);
            builder->addHash(IntegrityChecker::hashForFile(path).data());
            char * type;
            type = strchr(name,'.');
            if (type != NULL)
                builder->addType(type);
            char desc[DESC_LEGNTH];
            size_t desc_length;
            printf("Description:");
            getline((char**)&desc,&desc_length,stdin);
            builder->addDescription(desc);
            Publisher::getInstance()->publish(*builder->build());
        }
        else
        {
            printf("Path doesn't lead to a file!\n");
        }
    }
    else {
        printf("Invalid path\n");
    }
}

void CLI::processUnpublishRequest() {

}

void CLI::proccessDisconnectRequest() {

}
