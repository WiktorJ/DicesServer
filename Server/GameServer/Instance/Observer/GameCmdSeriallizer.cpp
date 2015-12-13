//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameCmdSeriallizer.h"

boost::property_tree::ptree GameCmdSeriallizer::serialize(boost::property_tree::ptree data, std::string cmd) {
    boost::property_tree::ptree newData;

    newData.put_child("command", boost::property_tree::ptree(cmd));
    newData.put_child("data", data);

    return newData;
}
