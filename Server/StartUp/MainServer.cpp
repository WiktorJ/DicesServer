//
// Created by Wojciech Grabis on 14.12.15.
//

#include <sys/socket.h>
#include "MainServer.h"
//#include "ConnectionServer.h"

MainServer::MainServer() {
    GameServer_ = new GameServer();
    try {
        GameServer_->start();
    } catch (std::exception *e) {
        std::cout<< e->what() <<std::endl;
    }
    try {
        connectionServer = new ConnectionServer(new WaitingRoom());
        connectionServer->init(9020);
        connectionServer->start();
    } catch (websocketpp::exception const &e) {
        std::cout << e.what() << std::endl;
    }
}

std::string MainServer::printGameInfo() {
    boost::property_tree::ptree gamesInfo = GameServer_->getActiveGames();

    std::stringstream ss;

    boost::property_tree::write_json(ss, gamesInfo);

    return ss.str();
}

void MainServer::stop() {
    GameServer_->stop();
}

void MainServer::temporaryClient(Client* test) {
    GameServer_->getWaitingRoom().addClient(test);
}
