//
// Created by Wojciech Grabis on 13.12.15.
//

#include "CmdDeseriallizer.h"

std::string CmdDeseriallizer::readCommand(boost::property_tree::ptree &data, int* gameId) {
    boost::property_tree::ptree newData;

    std::string command = data.get<std::string>("command");
    try {
        *gameId = data.get<int>("gameId");
    } catch(const boost::property_tree::ptree_error &exception){
        // do nothing
    }

    newData.put_child("command", data.get_child("command"));
    newData.put_child("data", data.get_child("data"));

    data = newData;
    return command;
}
