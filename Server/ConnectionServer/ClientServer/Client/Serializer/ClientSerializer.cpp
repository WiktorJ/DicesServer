//
// Created by wg on 12.01.16.
//

#include "ClientSerializer.h"

boost::property_tree::ptree ClientSerializer::serializeUserName(std::string ClientName, boost::property_tree::ptree data) {
    boost::property_tree::ptree result;

    result.put_child("clientName", boost::property_tree::ptree(ClientName));
    result.add_child("response", data);

    return result;
}

boost::property_tree::ptree ClientSerializer::serializeType(boost::property_tree::ptree data) {
    boost::property_tree::ptree result;

    result.put_child("type", boost::property_tree::ptree("clientInfo"));
    result.add_child("response", data);

    return result;
}
