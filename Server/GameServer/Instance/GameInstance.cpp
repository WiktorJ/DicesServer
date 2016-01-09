//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameInstance.h"

ClientGroup &GameInstance::getClientGroup() {
    return Clients;
}

GameInstance::GameInstance(GameController *Controller, JObserver Observer, WaitingRoom &WaitingRoom_, int GameId_/*, GameHolder& Holder_*/) : Controller(Controller), Clients(WaitingRoom_), Reader(Clients, Controller), Observer_(Clients, Observer), end(false), GameId_(GameId_), Logger("GameInstance")/*, Holder_(Holder_)*/{

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

    boost::this_thread::sleep(boost::posix_time::seconds(1000));

    Reader.stop();

    Logger.log("instance ended");
    end = true;
}

bool GameInstance::ended() {

    return end;
}

boost::property_tree::ptree GameInstance::getInfo(JNIEnv* TEnv) {
    return Controller->getGameInfo(TEnv);
}

int GameInstance::getId() {
    return GameId_;
}
