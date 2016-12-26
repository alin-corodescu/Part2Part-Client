//
// Created by alin on 12/21/16.
//

#ifndef CLIENT_PUBLISHER_H
#define CLIENT_PUBLISHER_H

#include <FileDescription.h>
#include "../network/Server.h"
#include <vector>

/**
 * class used to publish FileDescriptions
 * for other peers to use, as well as unpublish
 */
class Publisher {
public:
    Publisher(Server server);

    /**
     * @tag separate thread
     * @param files
     */
    void publish(std::vector<FileDescription> files);

    /**
     * @tag separate thread
     * @param file
     */
    void publish(FileDescription file);
};


#endif //CLIENT_PUBLISHER_H
