//
// Created by Wojciech Grabis on 16.12.15.
//

#include "ObsCmdDeserializer.h"

std::string ObsCmdDeserializer::deserialize(boost::property_tree::ptree &data) {
    std::string result = data.get<std::string>("command");

    data = data.get_child("data");
    return result;
}

std::string ObsCmdDeserializer::deserializeNick(boost::property_tree::ptree data) {
    return data.get<std::string>("nickname");
}
