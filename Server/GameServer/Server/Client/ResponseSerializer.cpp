//
// Created by wg on 08.01.16.
//

#include <boost/property_tree/ptree.hpp>
#include "ResponseSerializer.h"

boost::property_tree::ptree ResponseSerializer::getPositiveResponse(std::string command, std::string data) {
    boost::property_tree::ptree result;

    result.put_child("type", boost::property_tree::ptree("Response"));
    result.put_child("target", boost::property_tree::ptree("GameServer"));
    result.put_child("result", boost::property_tree::ptree("Success"));
    result.put_child("command", boost::property_tree::ptree(command));
    result.put_child("data", boost::property_tree::ptree(data));

    return result;
}

boost::property_tree::ptree ResponseSerializer::getNegativeResponse(std::string command, std::string data) {
    boost::property_tree::ptree result;

    result.put_child("type", boost::property_tree::ptree("Response"));
    result.put_child("target", boost::property_tree::ptree("GameServer"));
    result.put_child("result", boost::property_tree::ptree("Failure"));
    result.put_child("command", boost::property_tree::ptree(command));
    result.put_child("data", boost::property_tree::ptree(data));

    return result;
}
