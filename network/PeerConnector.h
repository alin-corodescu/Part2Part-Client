//
// Created by alin on 12/27/16.
//

#ifndef CLIENT_PEERCONNECTOR_H
#define CLIENT_PEERCONNECTOR_H


class PeerConnector {
private:
    FileDescription fileDescription;
    std::vector<Address> addresses;
    void _attemptConnections();
public:
    PeerConnector(FileDescription fileDescription,
                    std::vector<Address> addresses);
    void start();
};


#endif //CLIENT_PEERCONNECTOR_H
