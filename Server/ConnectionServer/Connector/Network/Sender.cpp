//
// Created by Wojciech Grabis on 08.12.15.
//

#include "Sender.h"

void Sender::send(boost::property_tree::ptree data) {
    stringstream ss;
    try {
        boost::property_tree::write_json(ss, data);
    } catch (const boost::property_tree::json_parser_error){
        Logger.log("Couldnt parse a json");
        return;
    }
    socket->sendData(ss.str(), socketId);
}

Sender::Sender(ConnectionServer* server, std::string socketId) : socketId(socketId), Logger("Sender"){
    socket = server;
}
