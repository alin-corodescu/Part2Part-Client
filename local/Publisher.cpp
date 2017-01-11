//
// Created by alin on 12/21/16.
//

#include <CommandBuilder.h>
#include "Publisher.h"
#include "storage/Cacher.h"

Publisher* Publisher::instance;
Publisher::Publisher(Server* server)  {
    this->instance = this;
    this->server = server;
}

void Publisher::publish(std::vector<FileDescription*> files) {
    unsigned int numberOfFileDescriptions = files.size();
    CommandBuilder commandBuilder;
    commandBuilder.setType(PUBLISH);
    commandBuilder.addArgument(numberOfFileDescriptions,INT);
    for (unsigned int i = 0 ; i < numberOfFileDescriptions; i++) {
        commandBuilder.addArgument(files[i]);
       // delete files[i];
    }

    Command* publish = commandBuilder.build();

    server->executeCommand(publish);


}

FileDescription* Publisher::publish(FileDescription* file) {
    std::vector<FileDescription*> files;

    files.push_back(file);
    publish(files);

    return file;
}

Publisher *Publisher::getInstance() {
    return instance;
}
