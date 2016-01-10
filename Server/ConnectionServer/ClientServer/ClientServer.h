//
// Created by wiktor on 21.12.15.
//

#ifndef DICESSERVER_CLIENTSERVER_H
#define DICESSERVER_CLIENTSERVER_H

#include <vector>
#include <map>
#include "Client/Client.h"
#include "../../GameServer/Server/Client/WaitingRoom.h"
#include "../Connector/Network/Sender.h"

class Sender;
class Client;
class WaitingRoom;

class ClientServer {


private:
    std::map <std::string, std::vector<Client*>> clients;
    WaitingRoom* waitingRoom;

public:
    void addClient(std::string name, std::string clientAddress, Sender* sender);
    bool removeClient(std::string clientAddress, std::string name);
    Client* getClient(std::string clientAddress, std::string name);
    void addClientEndpoint(std::string clientAddress);
    void removeClientEndpoint(std::string clientAddress);
    std::vector<Client *> getClientList(std::string clientAddress);
    ClientServer(WaitingRoom* waitingRoom);
};


#endif //DICESSERVER_CLIENTSERVER_H
