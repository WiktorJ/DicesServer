//
// Created by wg on 17.01.16.
//

#include "MessageHandle.h"
#include "Exception/ConnMessageException.h"
#include "Exception/ClientMessageException.h"

MessageHandle::MessageHandle(std::string message) : Command_(""){
    std::stringstream ss(message);
    deserialized = false;

    try {
        boost::property_tree::read_json(ss, Data);
    } catch(const boost::property_tree::json_parser_error &exception){
        throw ConnMessageException();
    }

    try{
        ClientID = Data.get<std::string>("clientID");
        Command_ = Command(Data.get<std::string>("type"));
    } catch(const boost::property_tree::ptree_error & exception){
        throw ConnMessageException();
    }

    try{
        Data = Data.get_child("request");
        Request = true;
    } catch(const boost::property_tree::ptree_error & exception){
        Request = false;
    }

}

ConnCommand MessageHandle::getCommand() {
    return Command_.getCommand();
}

std::string MessageHandle::getClientID() {
    return ClientID;
}


void MessageHandle::deserializeClientRequest() {
    if(!Request) throw ConnMessageException();

    try{
        ClientName = Data.get<std::string>("clientName");
    } catch(const boost::property_tree::ptree_error){
        throw ClientMessageException();
    }

    try{
        ClientRequest_ = Data.get_child("request");
        ClientRequest = true;
    } catch(const boost::property_tree::ptree_error){
        ClientRequest = false;
    }

    deserialized = true;
}

std::string MessageHandle::getClientName() {
    if(!deserialized)deserializeClientRequest();

    return ClientName;
}

boost::property_tree::ptree MessageHandle::getClientRequest() {
    if(!ClientRequest) throw ClientMessageException();

    return ClientRequest_;
}
