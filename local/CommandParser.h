//
// Created by alin on 12/27/16.
//

#ifndef CLIENT_COMMANDPARSER_H
#define CLIENT_COMMANDPARSER_H


class CommandParser {
    friend class Server;
private:
    int socketDescriptor;
protected:
    CommandParser(int socketDescriptor);
public:
    void parseResults();
};


#endif //CLIENT_COMMANDPARSER_H
