//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameInstance.h"

ClientGroup &GameInstance::getClientGroup() {
    return Clients;
}

GameInstance::GameInstance(GameController *Controller, WaitingRoom &WaitingRoom_) : Controller(Controller), Clients(WaitingRoom_), Reader(Clients, Controller), Observer_(Clients), end(false){

}

GameInstance::~GameInstance() {
    delete Controller;
}

void GameInstance::start() {
    Thread = boost::thread(boost::bind(&GameInstance::run, this));
}

void GameInstance::stop() {
    end = true;
    Reader.stop();

    Thread.interrupt();
    Thread.join();
}

void GameInstance::run() {
    Observer_.listen(); //TODO remember to add break points

    Reader.stop();
    end = true;
}

bool GameInstance::ended() {
    return end;
}

boost::property_tree::ptree GameInstance::getInfo() {
    return Controller->getGameInfo();
}
