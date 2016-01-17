//
// Created by wg on 17.01.16.
//

#ifndef DICESSERVER_MESSAGEHANDLE_H
#define DICESSERVER_MESSAGEHANDLE_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Command.h"
#include "../../../Logger/LogParser.h"

class MessageHandle {
private:
    Command Command_;
    std::string ClientID;
    bool Request;
    boost::property_tree::ptree Data;

    bool deserialized;
    bool ClientRequest;
    std::string ClientName;
    boost::property_tree::ptree ClientRequest_;
    void deserializeClientRequest();
public:
    MessageHandle(std::string message);
    ConnCommand getCommand();
    std::string getClientID();
    std::string getClientName();
    boost::property_tree::ptree getClientRequest();

};


#endif //DICESSERVER_MESSAGEHANDLE_H
