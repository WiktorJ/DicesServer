//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameController.h"
#include "../../Java/Instance/JNIInstance.h"
#include <boost/property_tree/json_parser.hpp>

boost::property_tree::ptree GameController::getGameInfo(JNIEnv* TEnv) {

    std::string info = Controller.getGameInfo(TEnv);
    std::stringstream ss(info);

    boost::property_tree::ptree json;

    try {
        boost::property_tree::read_json(ss, json);
    } catch (const boost::property_tree::json_parser_error &e){
        Logger.log("JSON Parser error, cannot get game info");

        //TODO THROW SOMETHING
    }
    return json;
}

void GameController::removePlayer(std::string username) {
    Logger.log("Removing player");

    Controller.removePlayer(username);
}

void GameController::makeMove(boost::property_tree::ptree moveInfo) {
    try {
        std::stringstream ss;
        boost::property_tree::write_json(ss, moveInfo);

        Controller.makeMove(ss.str());
    } catch(const boost::property_tree::json_parser_error &e){
        Logger.log("JSON Parser error, cannot request move");
    }
}

void GameController::addPlayer(std::string username) {
    Logger.log("Adding player" + username);

    Controller.addPlayer(username);
}

GameController::GameController(const GameController &other) : Controller(other.Controller), Logger(other.Logger){

}

GameController::GameController(JController Controller) : Controller(Controller), Logger("GameController"){

}

void GameController::bind() {
    Controller.attach(JNIInstance::getInstance().attacheThread());
}

void GameController::stop() {
    Logger.log("Stopping game controller");

    Controller.stop();
}

GameController::~GameController() {
    stop();
}
