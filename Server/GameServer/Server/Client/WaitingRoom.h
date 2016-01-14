//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_WAITINGROOM_H
#define DICESSERVER_WAITINGROOM_H


#include <vector>
#include <boost/thread/pthread/mutex.hpp>
#include "../../../ConnectionServer/ClientServer/Client/Client.h"
#include "../../../Logger/LogParser.h"

class Client;
//TODO MONITOR

class WaitingRoom {
private:
    boost::shared_ptr<boost::mutex> Mutex;
    LogParser Logger;
    std::vector<Client *> Clients;
    RequestQueue Requests;
    WaitingRoom(const WaitingRoom &other);

public:
    WaitingRoom();

    void sendDataToClient(std::string username, boost::property_tree::ptree data);
    void addClient(Client* client);
    Client* removeClient(std::string username);
    std::vector<ClientMovement> getRequests();
};


#endif //DICESSERVER_WAITINGROOM_H
