//
// Created by Wojciech Grabis on 13.12.15.
//

#include "ClientGroup.h"

ClientGroup::ClientGroup(WaitingRoom & WaitingRoom_) : WaitingRoom_(WaitingRoom_), Mutex(new boost::mutex){

}

void ClientGroup::sendData(boost::property_tree::ptree data) {
    Mutex->lock();

    for(std::vector<Client *>::iterator it = Subscribers.begin(); it != Subscribers.end(); it++)
        (*it)->sendData(data);

    Mutex->unlock();
}

void ClientGroup::addSubscriber(Client* client) {
    Mutex->lock();

    client->subscribe(&Requests);
    Subscribers.push_back(client);

    Mutex->unlock();
}

void ClientGroup::removeSubscriber(std::string username) {
    Mutex->lock();

    for(std::vector<Client *>::iterator it = Subscribers.begin(); it != Subscribers.end(); it++)
        if((*it)->getUsername() == username){
            Client* subscriber = (*it);

            Subscribers.erase(it);

            WaitingRoom_.addClient(subscriber);
            return;
        }

    Mutex->unlock();
}

std::vector<ClientMovement> ClientGroup::getRequests() {
    return Requests.getRequests();
}

void ClientGroup::removeClient(std::string username) {
    Mutex->lock();

    for(std::vector<Client *>::iterator it = Subscribers.begin(); it != Subscribers.end(); it++)
        if((*it)->getUsername() == username){
            Client* subscriber = (*it);
            Subscribers.erase(it);

            delete subscriber;
            return;
        }

    Mutex->unlock();
}

ClientGroup::ClientGroup(const ClientGroup &other) : WaitingRoom_(other.WaitingRoom_), Subscribers(other.Subscribers), Requests(other.Requests){

}

void ClientGroup::clear() {
    Mutex->lock();

    std::vector<Client *>::iterator it = Subscribers.begin();
    while(it != Subscribers.end()){
        Client* subscriber = (*it);

        it = Subscribers.erase(it);

        WaitingRoom_.addClient(subscriber);
    }

    Mutex->unlock();
}
