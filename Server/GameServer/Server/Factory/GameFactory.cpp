//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameFactory.h"

GameInstance *GameFactory::createGame(boost::property_tree::ptree description, WaitingRoom& WaitingRoom_) {
    return new GameInstance(new GameController, WaitingRoom_, curr_id++);
}

GameFactory::GameFactory() {
    curr_id = 0;
}
