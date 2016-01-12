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
    boost::shared_ptr<boost::mutex> Mutex;
    std::vector<Client *> Subscribers;
    RequestQueue Requests;

    ClientGroup(const ClientGroup &other);
    WaitingRoom &WaitingRoom_;
public:
    ClientGroup(WaitingRoom &WaitingRoom_);

    void clear();
    void sendDataToPlayer(std::string username, boost::property_tree::ptree data, std::string command);
    void sendData(boost::property_tree::ptree data, std::string command);
    void addSubscriber(Client* client);
    void removeSubscriber(std::string username);
    void removeClient(std::string username);
    std::vector<ClientMovement> getRequests();
};


#endif //DICESSERVER_CLIENTGROUP_H
