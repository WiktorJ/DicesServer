//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMESSERIALIZER_H
#define DICESSERVER_GAMESSERIALIZER_H


#include <boost/property_tree/ptree_fwd.hpp>
#include "../../Instance/GameInstance.h"

class GamesSerializer {
public:
    static boost::property_tree::ptree serialize(std::vector<GameInstance *> games, JNIEnv* TEnv);
};


#endif //DICESSERVER_GAMESSERIALIZER_H
