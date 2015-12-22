//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMEFACTORY_H
#define DICESSERVER_GAMEFACTORY_H


#include "../../Instance/GameInstance.h"
#include "../../Java/Object/Factory/JFactory.h"

class GameFactory {
private:
    JNIEnv* Env;
    JFactory Factory;
    int curr_id;
    LogParser Logger;
public:
    GameFactory();
    void setEnv(JNIEnv* Env);
    GameInstance* createGame(boost::property_tree::ptree description, WaitingRoom& WaitingRoom_);
};


#endif //DICESSERVER_GAMEFACTORY_H
