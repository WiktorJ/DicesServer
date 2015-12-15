//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameInstance.h"

ClientGroup &GameInstance::getClientGroup() {
    return Clients;
}

GameInstance::GameInstance(GameController *Controller, WaitingRoom &WaitingRoom_, int GameId_/*, GameHolder& Holder_*/, jobject gco) : Controller(Controller), Clients(WaitingRoom_), Reader(Clients, Controller), Observer_(Clients, gco), end(false), GameId_(GameId_), Logger("GameInstance")/*, Holder_(Holder_)*/{

}

GameInstance::~GameInstance() {
    Logger.log("deleting");
    if(!end)stop();

    delete Controller;
}

void GameInstance::start() {
    Logger.log("starting");
    Thread = boost::thread(boost::bind(&GameInstance::run, this));

    Reader.start();
}

void GameInstance::stop() {
    end = true;
    Logger.log("stopping");
    Reader.stop();

    Thread.interrupt();
    Thread.join();
    Logger.log("stopped");

    //Holder_.remove(GameId_);
}

void GameInstance::run() {
    Observer_.listen(); //TODO remember to add break points


    Reader.stop();

    Logger.log("instance ended");
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
