//
// Created by alin on 12/28/16.
//

#include "NATTraversalUtils.h"

int NATTraversalUtils::reusableSocket(unsigned short port) {
    int optval = 1;

    struct sockaddr_in local;

    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);

    /*
     * socket descriptori utilizati pentru hole punching,
     * vor folosi acelasi sockaddr_in (local)
     */
    int socketDesc;
    socketDesc = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(socketDesc,SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(socketDesc,SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    bind(socketDesc, (struct sockaddr *) &local, sizeof(struct sockaddr));

    return socketDesc;
}
