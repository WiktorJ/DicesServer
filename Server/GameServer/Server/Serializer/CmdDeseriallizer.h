//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_CMDDESERIALLIZER_H
#define DICESSERVER_CMDDESERIALLIZER_H


#include <boost/property_tree/ptree.hpp>
#include "../../Instance/GameInstance.h"

class CmdDeseriallizer {
public:
    static std::string readCommand(boost::property_tree::ptree& data, int* gameId);
};


#endif //DICESSERVER_CMDDESERIALLIZER_H
