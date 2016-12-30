//
// Created by alin on 12/26/16.
//

#include "QueryExecutor.h"
#include "CommandBuilder.h"
#include "../network/ConnectionHandler.h"
#include "Command.h"

void QueryExecutor::execute() {
    CommandBuilder commandBuilder;

    commandBuilder.setType(CommandTypes::QUERY);
    commandBuilder.addArgument(this->query);
    Command command = commandBuilder.build();

    ConnectionHandler *connectionHandler = ConnectionHandler::getInstance();
    connectionHandler->getServer().executeCommand(command);
}

QueryExecutor::QueryExecutor(FileDescription query) {
    this -> query = new FileDescription(query);
}
