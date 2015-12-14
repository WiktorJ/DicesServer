//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_CLIENTMOVEMENT_H
#define DICESSERVER_CLIENTMOVEMENT_H


#include <string>
#include <boost/property_tree/ptree.hpp>

class ClientMovement {
private:
    std::string Username;
    bool Player;
    boost::property_tree::ptree Move;
public:
    ClientMovement(std::string Username, bool Player, boost::property_tree::ptree Move);
    ClientMovement(const ClientMovement& other);
    std::string getUsername();
    boost::property_tree::ptree getMove();
    bool isPlayer();
};


#endif //DICESSERVER_CLIENTMOVEMENT_H
