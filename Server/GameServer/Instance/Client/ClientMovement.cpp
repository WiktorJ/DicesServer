//
// Created by Wojciech Grabis on 13.12.15.
//

#include "ClientMovement.h"

ClientMovement::ClientMovement(std::string Username, bool Player, std::string Move) : Username(Username), Player(Player), Move(Move){ }


std::string ClientMovement::getUsername() {
    return Username;
}

std::string ClientMovement::getMove() {
    return Move;
}

bool ClientMovement::isPlayer() {
    return Player;
}
