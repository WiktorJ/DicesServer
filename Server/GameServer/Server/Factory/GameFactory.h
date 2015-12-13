//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMEFACTORY_H
#define DICESSERVER_GAMEFACTORY_H


#include "../../Instance/GameInstance.h"

class GameFactory {
public:
    GameInstance* createGame(boost::property_tree::ptree description);
};


#endif //DICESSERVER_GAMEFACTORY_H
