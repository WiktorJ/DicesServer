//
// Created by Wojciech Grabis on 13.12.15.
//

#include "WaitingRoom.h"
#include "../../Instance/Client/ClientReader.h"

WaitingRoom::WaitingRoom() : Mutex(new boost::mutex){

}

void WaitingRoom::addClient(Client *client) {
    Mutex->lock();

    client->subscribe(&Requests);
    Clients.push_back(client);

    Mutex->unlock();
}

Client *WaitingRoom::removeClient(std::string username) {
    Mutex->lock();

    for(std::vector<Client *>::iterator it = Clients.begin(); it != Clients.end(); it++)
        if((*it)->getUsername() == username){
            Client* result = (*it);

            Clients.erase(it);

            return result;
        }

    Mutex->unlock();

    return NULL;
}

std::vector<ClientMovement> WaitingRoom::getRequests() {
    return Requests.getRequests();
}

WaitingRoom::WaitingRoom(const WaitingRoom &other) : Clients(other.Clients), Requests(other.Requests), Mutex(other.Mutex){

}

void WaitingRoom::sendActiveGames(std::string username, boost::property_tree::ptree activeGames) {
    Mutex->lock();

    for(std::vector<Client *>::iterator it = Clients.begin(); it != Clients.end(); it++)
        if((*it)->getUsername() == username){
            (*it)->sendData(activeGames);
        }

    Mutex->unlock();
}
