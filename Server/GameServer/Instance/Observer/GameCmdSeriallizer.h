//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMECMDSERIALLIZER_H
#define DICESSERVER_GAMECMDSERIALLIZER_H


#include <boost/property_tree/ptree.hpp>
#include <string>

class GameCmdSeriallizer {
public:
    boost::property_tree::ptree serialize(boost::property_tree::ptree data, std::string cmd);
};


#endif //DICESSERVER_GAMECMDSERIALLIZER_H
