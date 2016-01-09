//
// Created by Wojciech Grabis on 14.12.15.
//

#include <sys/socket.h>
#include "MainServer.h"
#include "../GameServer/Java/Instance/JConfig.h"

MainServer::MainServer() : Logger("MainServer"){
    state = true;
    try {
        JConfig::getInstance();
        GameServer_ = new GameServer;
    } catch(std::exception *exception){
        Logger.log("failed to create");
        throw new std::exception;
        state = false;
    }

    try {
        connectionServer = new ConnectionServer(&GameServer_->getWaitingRoom());
        connectionServer->init(9020);
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
    state = false;

    GameServer_->stop();
    connectionServer->stop();
}


void MainServer::temporaryClient(Client* test) {
    if(state)GameServer_->getWaitingRoom().addClient(test);
}

void MainServer::start() {
    if(state)GameServer_->start();
    if(state)connectionServer->start();
}

MainServer::~MainServer() {
    if(state) {
        stop();
    }
    delete GameServer_;
    delete connectionServer;
//    GameServer_->getWaitingRoom().addClient(test);
}
