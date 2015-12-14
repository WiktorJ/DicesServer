//
// Created by Wojciech Grabis on 13.12.15.
//

#include "ClientMovement.h"

ClientMovement::ClientMovement(std::string Username, bool Player, boost::property_tree::ptree Move) : Username(Username), Player(Player), Move(Move){ }


std::string ClientMovement::getUsername() {
    return Username;
}

boost::property_tree::ptree ClientMovement::getMove() {
    return Move;
}

bool ClientMovement::isPlayer() {
    return Player;
}

ClientMovement::ClientMovement(const ClientMovement &other) : Username(other.Username), Player(other.Player), Move(other.Move){

}
