//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameController.h"
#include "../../Java/Instance/JNIInstance.h"
#include <boost/property_tree/json_parser.hpp>

boost::property_tree::ptree GameController::getGameInfo() {
    return boost::property_tree::ptree("testControler");
}

void GameController::removePlayer(std::string username) {
    Controller.removePlayer(username);
}

void GameController::makeMove(boost::property_tree::ptree moveInfo) {
    std::stringstream ss;
    boost::property_tree::write_json(ss, moveInfo);

    Controller.makeMove(ss.str());

}

void GameController::addPlayer(std::string username) {
    Controller.addPlayer(username);
}

GameController::GameController(const GameController &other) : Controller(other.Controller){

}

GameController::GameController(JController Controller) : Controller(Controller){

}

void GameController::bind() {
    Controller.attach(JNIInstance::getInstance().attacheThread());
}

void GameController::stop() {
    Controller.stop();
}

GameController::~GameController() {
    stop();
}
