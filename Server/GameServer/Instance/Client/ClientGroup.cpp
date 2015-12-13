//
// Created by Wojciech Grabis on 13.12.15.
//

#include "ClientGroup.h"
#include "ClientReader.h"

ClientGroup::ClientGroup(WaitingRoom & WaitingRoom_) : WaitingRoom_(WaitingRoom_){

}

void ClientGroup::sendData(std::string data) {
    for(std::vector<Client *>::iterator it = Subscribers.begin(); it != Subscribers.end(); it++)
        (*it)->sendData(data);
}

void ClientGroup::addSubscriber(Client* client) {
    Subscribers.push_back(client);
}

void ClientGroup::removeSubscriber(std::string username) {
    for(std::vector<Client *>::iterator it = Subscribers.begin(); it != Subscribers.end(); it++)
        if((*it)->getUsername() == username){
            Client* subscriber = (*it);
            Subscribers.erase(it);

            WaitingRoom_.addClient(subscriber);
        }
}

std::vector<ClientMovement> ClientGroup::getRequests() {
    return ClientReader::getPlayerMoves(Subscribers);
}

void ClientGroup::removeClient(std::string username) {
    for(std::vector<Client *>::iterator it = Subscribers.begin(); it != Subscribers.end(); it++)
        if((*it)->getUsername() == username){
            Client* subscriber = (*it);
            Subscribers.erase(it);

            delete subscriber;
        }
}
