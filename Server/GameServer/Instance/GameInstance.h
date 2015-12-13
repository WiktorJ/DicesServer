//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMEINSTANCE_H
#define DICESSERVER_GAMEINSTANCE_H


#include "Client/ClientGroup.h"
#include "Observer/Observer.h"
#include "Reader/GameReader.h"

class GameInstance {
private:
    ClientGroup Clients;
    Observer Observer_;
    GameReader Reader;
    GameController* Controller;

    boost::thread Thread;
    void run();
public:
    GameInstance(GameController* Controller, WaitingRoom& WaitingRoom_);
    ~GameInstance();
    void start();
    ClientGroup& getClientGroup();
    void stop();
};


#endif //DICESSERVER_GAMEINSTANCE_H
