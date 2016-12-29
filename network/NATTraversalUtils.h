//
// Created by alin on 12/28/16.
//

#ifndef CLIENT_NATTRAVERSALUTILS_H
#define CLIENT_NATTRAVERSALUTILS_H


#include <netinet/in.h>
#include "Address.h"

#define START_PORT 5000
class NATTraversalUtils {
public:
    static unsigned short PORT = START_PORT;

    static int reusableSocket();

    static void obtainNATPort(Address &a, int socket);

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
