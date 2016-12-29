//
// Created by alin on 12/21/16.
//

#include <CommandBuilder.h>
#include "Publisher.h"

Publisher::Publisher(Server server) : server(server) {
}

void Publisher::publish(std::vector<FileDescription> files) {
    unsigned int numberOfFileDescriptions = files.size();
    CommandBuilder commandBuilder;
    commandBuilder.setType(PUBLISH);
    commandBuilder.addArgument(numberOfFileDescriptions);
    for (unsigned int i = 0 ; i < numberOfFileDescriptions; i++)
        commandBuilder.addArgument(files[i]);

    Command publish = commandBuilder.build();

    server.executeCommand(publish);

}

void Publisher::publish(FileDescription file) {
    std::vector<FileDescription> files;
    files.push_back(file);
    publish(files);
}
