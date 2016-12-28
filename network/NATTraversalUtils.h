//
// Created by alin on 12/28/16.
//

#ifndef CLIENT_NATTRAVERSALUTILS_H
#define CLIENT_NATTRAVERSALUTILS_H


#include <netinet/in.h>

class NATTraversalUtils {

    static int reusableSocket(unsigned short port);
};


#endif //CLIENT_NATTRAVERSALUTILS_H
