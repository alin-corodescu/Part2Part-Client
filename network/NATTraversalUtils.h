//
// Created by alin on 12/28/16.
//
#pragma once
#ifndef CLIENT_NATTRAVERSALUTILS_H
#define CLIENT_NATTRAVERSALUTILS_H


#include <netinet/in.h>
#include "Address.h"

#define START_PORT 5000
class NATTraversalUtils {
public:
    static unsigned short PORT = START_PORT;

    static int reusableSocket();

    /**
     * obtaints the new address used for hole punching
     * using the socket to communicate with the server
     * @param a
     * @param socket
     */
    static void obtainNATPort(Address &a, int socket);

    static void notify(Address &a, int server);

    static void connectThrough(int socket,unsigned int ip,unsigned short port);

    /**
     * attemps to punch a "hole" in the NAT of the peer
     * @param peer - address where the peer is listening / attempting connection
     * @param requester - socket through which to request connections
     * @param accepter - socket on which to accept connections
     * @return a socket descriptor of the established connection
     */
    static int holePunch(Address peer, int requester,int accepter);
};




#endif //CLIENT_NATTRAVERSALUTILS_H
