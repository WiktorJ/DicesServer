//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMECONTROLLER_H
#define DICESSERVER_GAMECONTROLLER_H

#include <string>
#include <boost/property_tree/ptree.hpp>

//TODO CONNECT WITH JAVA
class GameController {
public:
    GameController(const GameController &other);
    GameController();
    void addPlayer(std::string username);
    void makeMove(boost::property_tree::ptree moveInfo);
    void removePlayer(std::string username);
    boost::property_tree::ptree getGameInfo();
};


#endif //DICESSERVER_GAMECONTROLLER_H
