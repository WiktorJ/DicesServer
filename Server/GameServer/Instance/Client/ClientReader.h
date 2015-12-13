//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_CLIENTREADER_H
#define DICESSERVER_CLIENTREADER_H


#include <vector>
#include "../../../ConnectionServer/ClientServer/Client/Client.h"
#include "ClientMovement.h"

class ClientReader {
public:
    static std::vector<ClientMovement> getPlayerMoves(std::vector<Client *> clients);
};


#endif //DICESSERVER_CLIENTREADER_H
