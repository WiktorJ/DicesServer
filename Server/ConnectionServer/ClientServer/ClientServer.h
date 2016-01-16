//
// Created by wiktor on 21.12.15.
//

#ifndef DICESSERVER_CLIENTSERVER_H
#define DICESSERVER_CLIENTSERVER_H

#include <vector>
#include <map>
#include <set>
#include "Client/Client.h"
#include "../../GameServer/Server/Client/WaitingRoom.h"
#include "../Connector/Network/Sender.h"
#include "../../Logger/LogParser.h"

class Sender;
class Client;
class WaitingRoom;

class ClientServer {


private:
    boost::shared_ptr<boost::mutex> Mutex;
    std::set <std::string> ClientNames;
    std::map <std::string, std::vector<Client*>> clients;
    LogParser Logger;
    WaitingRoom* waitingRoom;

public:
    void addClient(std::string name, std::string clientAddress, Sender* sender);
    void removeClient(std::string clientAddress, std::string name);
    Client* getClient(std::string clientAddress, std::string name);
    void addClientEndpoint(std::string clientAddress);
    void removeClientEndpoint(std::string clientAddress);
    std::vector<Client *> getClientList(std::string clientAddress);
    ClientServer(WaitingRoom* waitingRoom);
};


#endif //DICESSERVER_CLIENTSERVER_H
