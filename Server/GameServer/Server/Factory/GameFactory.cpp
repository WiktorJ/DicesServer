//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameFactory.h"
#include "../../Java/Exception/JNIException.h"

GameInstance *GameFactory::createGame(boost::property_tree::ptree description, WaitingRoom& WaitingRoom_) {

    std::stringstream ss;

    boost::property_tree::write_json(ss, description);

    std::string converted = ss.str();

    JObserver Observer;
    Observer.attach(Env);
    Observer.initialize();


    JController Controller = Factory.createGame(converted, Observer);

    GameInstance* game = new GameInstance(new GameController(Controller), Observer, WaitingRoom_, curr_id++);

    return game;
}

GameFactory::GameFactory() : Logger("GameFactory"){
    try {
        Env = JNIInstance::getInstance().attacheThread();
        Factory.attach(Env);
    } catch(const JNIException &exception){
        Logger.log("Failed to attach");

        // TODO IMPORTANTE EXCEPTION

        throw new std::exception;
    }
    curr_id = 0;
}
