//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMECMDDESERIALLIZER_H
#define DICESSERVER_GAMECMDDESERIALLIZER_H

#include<string>
#include <boost/property_tree/ptree.hpp>

class GameCmdDeseriallizer {
public:
    static std::string ReadCommand(boost::property_tree::ptree& data);
};


#endif //DICESSERVER_GAMECMDDESERIALLIZER_H
