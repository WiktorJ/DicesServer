//
// Created by wg on 16.01.16.
//

#include "ConnectorResponseSerializer.h"

boost::property_tree::ptree ConnectorResponseSerializer::serializeType(boost::property_tree::ptree response) {
    boost::property_tree::ptree result;

    result.put_child("type", boost::property_tree::ptree("connectorInfo"));
    result.add_child("response", response);

    return result;
}

boost::property_tree::ptree ConnectorResponseSerializer::serializeResponse(std::string command, status status_) {
    boost::property_tree::ptree result;

    result.put_child("command", boost::property_tree::ptree(command));

    switch(status_){
        case status::FAILURE :
            result.put_child("status", boost::property_tree::ptree("FAILURE"));
            break;
        case status::SUCCESS :
            result.put_child("status", boost::property_tree::ptree("SUCCESS"));
            break;
        default:
            result.put_child("status", boost::property_tree::ptree("UNKNOWN"));
            break;
    }

    return result;
}
