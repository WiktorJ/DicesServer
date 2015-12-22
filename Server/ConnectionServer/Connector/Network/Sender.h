//
// Created by Wojciech Grabis on 08.12.15.
//



#ifndef DICESSERVER_SENDER_H
#define DICESSERVER_SENDER_H

class ConnectionServer;

#include "../../ClientServer/ClientServer.h"
#include "../../ClientServer/ConnectionServer.h"
class Sender {
private:
    ConnectionServer* socket;
    std::string socketId;

public:
    Sender(ConnectionServer* server, std::string socketId);
    void send(std::string data);
    void receive();
};


#endif //DICESSERVER_SENDER_H
