//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameCmdDeseriallizer.h"

std::string GameCmdDeseriallizer::ReadCommand(boost::property_tree::ptree &data) {

    boost::property_tree::ptree command= data.get_child("command");

    data = data.get_child("data");

    return command.get_value();
}
