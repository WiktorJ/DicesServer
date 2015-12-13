//
// Created by Wojciech Grabis on 13.12.15.
//

#include "ClientReader.h"

std::vector<ClientMovement> ClientReader::getPlayerMoves(std::vector<Client *> clients) {
    std::vector<ClientMovement> result;

    for(std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++){
        std::string request = (*it)->getRequest();
        //TODO EXCEPTION HANDLE

        ClientMovement move((*it)->getUsername(), (*it)->isPlayer(), request);
        result.push_back(move);
    }

    return result;
}
