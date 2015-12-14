//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMEFACTORY_H
#define DICESSERVER_GAMEFACTORY_H


#include "../../Instance/GameInstance.h"

class GameFactory {
private:
    int curr_id;
public:
    GameFactory();
    GameInstance* createGame(boost::property_tree::ptree description, WaitingRoom& WaitingRoom_);
};


#endif //DICESSERVER_GAMEFACTORY_H
