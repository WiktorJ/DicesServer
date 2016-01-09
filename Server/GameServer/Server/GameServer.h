//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMESERVER_H
#define DICESSERVER_GAMESERVER_H


#include <vector>
#include "../Instance/GameInstance.h"
#include "Factory/GameFactory.h"
#include "GameHolder.h"
#include "../../Logger/LogParser.h"

class GameServer {
private:
    GameHolder Games;
    WaitingRoom WaitingRoom_;
    GameFactory Factory;
    boost::thread Thread;
    LogParser Logger;
    JNIEnv* Env;

    void readRequests();
    void run();
public:
    GameServer();
    void start();
    boost::property_tree::ptree getActiveGames();
    WaitingRoom& getWaitingRoom();
    void stop();
};


#endif //DICESSERVER_GAMESERVER_H
