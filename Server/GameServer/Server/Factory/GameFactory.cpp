//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameFactory.h"
#include "../../Java/Exception/JNIException.h"

GameInstance *GameFactory::createGame(boost::property_tree::ptree description, WaitingRoom& WaitingRoom_) {

    std::stringstream ss;

    boost::property_tree::write_json(ss, description);

    std::string converted = ss.str();

    JObserver Observer(Env);
    Observer.attach(Env);
    Observer.create();

    JController Controller = Factory.createGame(converted, Observer);

    GameInstance* game = new GameInstance(new GameController(Controller), Observer, WaitingRoom_, curr_id++);

    return game;
}

GameFactory::GameFactory() : Env(JNIInstance::getInstance().getCurr()), Logger("GameFactory"), Factory(Env){
    Logger.log("Trying to attach JFactory");

    Factory.attach(Env);

    curr_id = 0;
}

void GameFactory::setEnv(JNIEnv *Env) {
    this->Env = Env;
    Factory.attach(Env);
}
