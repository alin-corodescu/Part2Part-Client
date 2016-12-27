//
// Created by alin on 12/26/16.
//

#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H


enum CommandTypes {
    QUERY,
    JOIN,
    PUBLISH,
    FIND,
    UNPUBLISH,
    NOTIFIY,
    BYE,
    RESULTS,
    REQUEST,
    OPEN,
    PROVIDE,
    TRASNFERRING
};

const char* commandName(CommandTypes type) {
    switch (type)
    {
        case QUERY: return "QUERY";
        case JOIN: return "JOIN";
        case PUBLISH: return "PUBLISH";
        case FIND: return "FIND";
        case UNPUBLISH: return "UNPUBLISH";
        case NOTIFIY: return "NOTIFIY";
        case BYE: return "BYE";
        case RESULTS: return "RESULTS";
        case REQUEST: return "REQUEST";
        case OPEN: return "OPEN";
        case PROVIDE: return "PROVIDE";
        case TRASNFERRING: return "TRANSFERRING";
    }
}
class Command {

};


#endif //CLIENT_COMMAND_H
