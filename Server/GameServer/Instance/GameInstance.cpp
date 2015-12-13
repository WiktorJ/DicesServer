//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameInstance.h"

ClientGroup &GameInstance::getClientGroup() {
    return Clients;
}

GameInstance::GameInstance(GameController *Controller, WaitingRoom &WaitingRoom_) : Controller(Controller), Clients(WaitingRoom_), Reader(Clients, Controller), Observer_(Clients){

}

GameInstance::~GameInstance() {
    delete Controller;
}

void GameInstance::start() {
    Thread = boost::thread(boost::bind(&GameInstance::run, this));
}

void GameInstance::stop() {
    Thread.interrupt();

    Thread.join();
}

void GameInstance::run() {
    while(true){
        Observer_.listen();

        boost::this_thread::interruption_point();
    }
}
