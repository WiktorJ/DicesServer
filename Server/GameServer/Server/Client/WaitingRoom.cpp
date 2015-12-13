//
// Created by Wojciech Grabis on 13.12.15.
//

#include "WaitingRoom.h"
#include "../../Instance/Client/ClientReader.h"

WaitingRoom::WaitingRoom() {

}

void WaitingRoom::addClient(Client *client) {
    Clients.push_back(client);
}

Client *WaitingRoom::removeClient(std::string username) {
    for(std::vector<Client *>::iterator it = Clients.begin(); it != Clients.end(); it++)
        if((*it)->getUsername() == username){
            Client* result = (*it);
            Clients.erase(it);
            return result;
        }
    //TODO
    return NULL;
}

std::vector<ClientMovement> WaitingRoom::getRequests() {
    return ClientReader::getPlayerMoves(Clients);
}

WaitingRoom::WaitingRoom(const WaitingRoom &other) : Clients(other.Clients){

}
