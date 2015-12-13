//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameServer.h"
#include "Serializer/GamesSerializer.h"

void GameServer::refreshGameList() {
    Mutex.lock();

    for(std::vector<GameInstance *>::iterator it = Games.begin(); it != Games.end(); ) {
        if ((*it)->ended()){
            delete (*it);
            it = Games.erase(it);
        }
        else it++;
    }

    Mutex.unlock();
}


WaitingRoom &GameServer::getWaitingRoom() {
    return WaitingRoom_;
}

boost::property_tree::ptree GameServer::getActiveGames() {
    Mutex.lock();

    boost::property_tree::ptree activeGames = GamesSerializer::serialize(Games);

    Mutex.unlock();
    return activeGames;
}
