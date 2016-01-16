//
// Created by Wojciech Grabis on 13.12.15.
//

#include "CmdDeseriallizer.h"

std::string CmdDeseriallizer::readCommand(boost::property_tree::ptree &data) {
    boost::property_tree::ptree newData;

    std::string command = data.get<std::string>("command");

    newData.put_child("command", data.get_child("command"));
    newData.put_child("data", data.get_child("data"));

    data = newData;
    return command;
}

int CmdDeseriallizer::getGameID(boost::property_tree::ptree data) {
    int gameID = -1;

    try{
        gameID = data.get<int>("data");
    } catch (const boost::property_tree::ptree_error)
    { }

    return gameID;
}
