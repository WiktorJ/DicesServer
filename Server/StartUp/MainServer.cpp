//
// Created by Wojciech Grabis on 14.12.15.
//

#include "MainServer.h"

MainServer::MainServer() {
    GameServer_.start();
}

std::string MainServer::printGameInfo() {
    boost::property_tree::ptree gamesInfo = GameServer_.getActiveGames();

    std::stringstream ss;

    boost::property_tree::write_json(ss, gamesInfo);

    return ss.str();
}

void MainServer::stop() {
    GameServer_.stop();
}

void MainServer::temporaryClient(Client* test) {
    GameServer_.getWaitingRoom().addClient(test);
}
