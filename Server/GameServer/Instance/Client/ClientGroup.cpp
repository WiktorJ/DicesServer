//
// Created by Wojciech Grabis on 13.12.15.
//

#include "ClientGroup.h"

ClientGroup::ClientGroup(WaitingRoom & WaitingRoom_) : WaitingRoom_(WaitingRoom_), Mutex(new boost::mutex){

}

void ClientGroup::sendData(boost::property_tree::ptree data) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    for(std::vector<Client *>::iterator it = Subscribers.begin(); it != Subscribers.end(); it++)
        (*it)->sendData(data);
}

void ClientGroup::addSubscriber(Client* client) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    client->subscribe(&Requests);
    Subscribers.push_back(client);
}

void ClientGroup::removeSubscriber(std::string username) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    for(std::vector<Client *>::iterator it = Subscribers.begin(); it != Subscribers.end(); it++)
        if((*it)->getUsername() == username){
            Client* subscriber = (*it);

            Subscribers.erase(it);

            WaitingRoom_.addClient(subscriber);
            return;
        }
}

std::vector<ClientMovement> ClientGroup::getRequests() {
    return Requests.getRequests();
}

void ClientGroup::removeClient(std::string username) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    for(std::vector<Client *>::iterator it = Subscribers.begin(); it != Subscribers.end(); it++)
        if((*it)->getUsername() == username){
            Client* subscriber = (*it);
            Subscribers.erase(it);

            delete subscriber;
            return;
        }

}

ClientGroup::ClientGroup(const ClientGroup &other) : WaitingRoom_(other.WaitingRoom_), Subscribers(other.Subscribers), Requests(other.Requests){

}

void ClientGroup::clear() {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    std::vector<Client *>::iterator it = Subscribers.begin();
    while(it != Subscribers.end()){
        Client* subscriber = (*it);

        it = Subscribers.erase(it);

        WaitingRoom_.addClient(subscriber);
    }
}

void ClientGroup::sendDataToPlayer(std::string username, boost::property_tree::ptree data) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    for(std::vector<Client *>::iterator it = Subscribers.begin(); it != Subscribers.end(); it++)
        if((*it)->getUsername() == username){
            (*it)->sendData(data);

            return;
        }
}
