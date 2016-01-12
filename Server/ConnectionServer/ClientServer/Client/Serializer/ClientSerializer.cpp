//
// Created by wg on 12.01.16.
//

#include "ClientSerializer.h"

boost::property_tree::ptree ClientSerializer::serialize(std::string ClientName, boost::property_tree::ptree data, std::string command) {
    boost::property_tree::ptree result;

    result.put_child("clientID", boost::property_tree::ptree(ClientName));
    result.put_child("command", boost::property_tree::ptree(command));
    result.add_child("data", data);

    return result;
}
