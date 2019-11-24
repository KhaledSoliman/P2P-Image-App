#ifndef DISTRIBUTED_SYSTEMS_FALL19_UDPSERVERSOCKET_H
#define DISTRIBUTED_SYSTEMS_FALL19_UDPSERVERSOCKET_H

#include "UDPSocket.h"

class UDPServerSocket : public UDPSocket {
public:
    UDPServerSocket();

    bool initializeServer(std::string _myAddr, int _myPort);

    ~UDPServerSocket();
};

#endif //DISTRIBUTED_SYSTEMS_FALL19_UDPSERVERSOCKET_H