//
// Created by alin on 12/27/16.
//
#pragma once
#ifndef CLIENT_COMMANDPARSER_H
#define CLIENT_COMMANDPARSER_H


class CommandParser {
    friend class Server;
private:
    int socketDescriptor;
    FileDescription* readFileDescription();
protected:
    CommandParser(int socketDescriptor);
public:
    void parseResults();
    void parseRequestFileFrom();
    void parseOpenCommand();
};


#endif //CLIENT_COMMANDPARSER_H
