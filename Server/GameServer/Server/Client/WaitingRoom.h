//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_WAITINGROOM_H
#define DICESSERVER_WAITINGROOM_H


#include <vector>
#include <boost/thread/pthread/mutex.hpp>
#include "../../../ConnectionServer/ClientServer/Client/Client.h"
#include "../../Instance/Client/ClientMovement.h"

//TODO MONITOR

class WaitingRoom {
private:
    boost::mutex Mutex;
    std::vector<Client *> Clients;
public:
    WaitingRoom();
    WaitingRoom(const WaitingRoom &other);
    void addClient(Client* client);
    Client* removeClient(std::string username);
    std::vector<ClientMovement> getRequests();
};


#endif //DICESSERVER_WAITINGROOM_H
