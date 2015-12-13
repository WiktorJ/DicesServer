//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_CLIENTMOVEMENT_H
#define DICESSERVER_CLIENTMOVEMENT_H


#include <string>

class ClientMovement {
private:
    std::string Username;
    bool Player;
    std::string Move;
public:
    ClientMovement(std::string Username, bool Player, std::string Move);
    std::string getUsername();
    std::string getMove();
    bool isPlayer();
};


#endif //DICESSERVER_CLIENTMOVEMENT_H
