//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMECONTROLLER_H
#define DICESSERVER_GAMECONTROLLER_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include "../../Java/Object/Controller/JController.h"

//TODO CONNECT WITH JAVA
class GameController {
private:
    JController Controller;
    LogParser Logger;
public:
    GameController(const GameController &other);
    GameController(JController Controller);
    ~GameController();
    void addPlayer(std::string username);
    void makeMove(boost::property_tree::ptree moveInfo);
    void removePlayer(std::string username);
    boost::property_tree::ptree getGameInfo(JNIEnv* TEnv);
    void stop();
    void bind();
};


#endif //DICESSERVER_GAMECONTROLLER_H
