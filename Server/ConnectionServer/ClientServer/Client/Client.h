//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_CLIENT_H
#define DICESSERVER_CLIENT_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>
#include "../../../GameServer/Event/RequestQueue.h"

//TODO MONITOR

class Client {
private:
    //Sender
    std::string Username;
    RequestQueue* Requests;
    bool Free;
    bool Player;
public:
    Client(std::string Username);
    std::string getUsername();

    void subscribe(RequestQueue* Requests);
    void addRequest(boost::property_tree::ptree Request);
    void sendData(std::string data);
    void setObserver();
    void setPlayer();
    bool isPlayer();
};


#endif //DICESSERVER_CLIENT_H
