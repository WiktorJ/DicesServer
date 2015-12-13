//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMEREADER_H
#define DICESSERVER_GAMEREADER_H


#include "../Client/ClientGroup.h"
#include "../Controller/GameController.h"

#include <boost/thread/thread.hpp>

class GameReader {
private:
    ClientGroup& Clients;
    boost::thread thread;
    GameController* Controller;
    
    void readMovement();
public:
    GameReader(ClientGroup& Clients, GameController* Controller);
    void start();
    void stop();
    void run();
};


#endif //DICESSERVER_GAMEREADER_H
