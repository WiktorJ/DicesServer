//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameInstance.h"

ClientGroup &GameInstance::getClientGroup() {
    return Clients;
}

GameInstance::GameInstance(GameController *Controller, WaitingRoom &WaitingRoom_, int GameId_/*, GameHolder& Holder_*/) : Controller(Controller), Clients(WaitingRoom_), Reader(Clients, Controller), Observer_(Clients), end(false), GameId_(GameId_)/*, Holder_(Holder_)*/{

}

GameInstance::~GameInstance() {
    if(!end)stop();

    delete Controller;
}

void GameInstance::start() {
    Thread = boost::thread(boost::bind(&GameInstance::run, this));

    Reader.start();
}

void GameInstance::stop() {
    end = true;
    Reader.stop();

    Thread.interrupt();
    Thread.join();

    //Holder_.remove(GameId_);
}

void GameInstance::run() {
    Observer_.listen(); //TODO remember to add break points

    Reader.stop();
    end = true;
}

bool GameInstance::ended() {
    //Holder_.remove(GameId_);

    return end;
}

boost::property_tree::ptree GameInstance::getInfo() {
    return Controller->getGameInfo();
}

int GameInstance::getId() {
    return GameId_;
}
