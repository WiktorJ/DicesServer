//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_CLIENT_H
#define DICESSERVER_CLIENT_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>

class Client {
private:
    //Sender
    std::string Username;
    boost::property_tree::ptree Request; // to json
    bool Blocked;
    bool Free;
    bool Player;
public:
    std::string getUsername();
    void addRequest(boost::property_tree::ptree Request);
    void sendData(std::string data);
    boost::property_tree::ptree getRequest();
    void setObserver();
    void setPlayer();
    bool isPlayer();
};


#endif //DICESSERVER_CLIENT_H
