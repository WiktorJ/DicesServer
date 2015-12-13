//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMESERVER_H
#define DICESSERVER_GAMESERVER_H


#include <vector>
#include "../Instance/GameInstance.h"
#include "Factory/GameFactory.h"
#include "GameHolder.h"

class GameServer {
private:
    GameHolder Games;
    WaitingRoom WaitingRoom_;
    GameFactory Factory;
    boost::thread Thread;

    void readRequests();
    void run();
private:
    void start();
    boost::property_tree::ptree getActiveGames();
    WaitingRoom& getWaitingRoom();
    void stop();
};


#endif //DICESSERVER_GAMESERVER_H
