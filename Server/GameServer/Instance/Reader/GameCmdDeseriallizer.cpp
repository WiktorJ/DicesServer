//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameCmdDeseriallizer.h"

std::string GameCmdDeseriallizer::readCommand(boost::property_tree::ptree &data) {

    boost::property_tree::ptree command= data;

    data = data.get_child("data");

    return command.get<std::string>("command");
}
