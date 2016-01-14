//
// Created by Wojciech Grabis on 13.12.15.
//

#include "WaitingRoom.h"

WaitingRoom::WaitingRoom() : Mutex(new boost::mutex), Logger("WaitingRoom"){

}

void WaitingRoom::addClient(Client *client) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    Logger.log("Adding client" + client->getUsername());

    client->subscribe(&Requests);
    Clients.push_back(client);
}

Client *WaitingRoom::removeClient(std::string username) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    for(std::vector<Client *>::iterator it = Clients.begin(); it != Clients.end(); it++)
        if((*it)->getUsername() == username){
            Client* result = (*it);

            Clients.erase(it);

            Logger.log("Removing client" + result->getUsername());

            return result;
        }

    return NULL;
}

std::vector<ClientMovement> WaitingRoom::getRequests() {
    return Requests.getRequests();
}

WaitingRoom::WaitingRoom(const WaitingRoom &other) : Clients(other.Clients), Requests(other.Requests), Mutex(other.Mutex), Logger(other.Logger){

}

void WaitingRoom::sendDataToClient(std::string username, boost::property_tree::ptree data) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    Logger.log("Sending data to user" + username);

    for(std::vector<Client *>::iterator it = Clients.begin(); it != Clients.end(); it++)
        if((*it)->getUsername() == username){
            (*it)->sendData(data);
        }

}