//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_CLIENTGROUP_H
#define DICESSERVER_CLIENTGROUP_H


#include <vector>
#include <string>
#include <boost/thread/pthread/mutex.hpp>
#include "../../../ConnectionServer/ClientServer/Client/Client.h"
#include "ClientMovement.h"
#include "../../Server/Client/WaitingRoom.h"

//TODO MONITOR

class ClientGroup {
private:
    boost::mutex Mutex;
    std::vector<Client *> Subscribers;
    WaitingRoom &WaitingRoom_;
public:
    ClientGroup(WaitingRoom &WaitingRoom_);
    ClientGroup(const ClientGroup &other);
    void sendData(std::string data);
    void addSubscriber(Client* client);
    void removeSubscriber(std::string username);
    void removeClient(std::string username);
    std::vector<ClientMovement> getRequests();
};


#endif //DICESSERVER_CLIENTGROUP_H
