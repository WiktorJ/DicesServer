//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_CLIENT_H
#define DICESSERVER_CLIENT_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>
#include "../../../GameServer/Event/RequestQueue.h"
#include "../../Connector/Network/Sender.h"

//TODO MONITOR
class Sender;

class Client {
private:
    Sender* sender;
    std::string Username;
    RequestQueue* Requests;
    bool Free;
    bool Player;
public:
    Client(std::string Username, Sender* sender);
    std::string getUsername();

    void subscribe(RequestQueue* Requests);
    void addRequest(boost::property_tree::ptree Request);
    void sendData(std::string data);
    void setObserver();
    void setPlayer();
    bool isPlayer();
};


#endif //DICESSERVER_CLIENT_H
