//
// Created by wg on 12.01.16.
//

#include "GameResponseSerializer.h"

boost::property_tree::ptree GameResponseSerializer::serializeResponse(std::string command, status Status,
                                                                      boost::property_tree::ptree data) {
    boost::property_tree::ptree result;

    result.put_child("command", boost::property_tree::ptree(command));

    switch(Status){
        case status::FAILURE :
            result.put_child("status", boost::property_tree::ptree("FAILURE"));
        case status::SUCCESS :
            result.put_child("status", boost::property_tree::ptree("SUCCESS"));
        default:
            result.put_child("status", boost::property_tree::ptree("UNKNOWN"));
    }

    result.add_child("data", data);

    return result;
}
