//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameController.h"
#include <boost/property_tree/json_parser.hpp>

boost::property_tree::ptree GameController::getGameInfo() {

}

void GameController::removePlayer(std::string username) {

}

void GameController::makeMove(boost::property_tree::ptree moveInfo) {
    /* temporary
     *
     */
    std::stringstream ss;
    boost::property_tree::read_json(ss, moveInfo);

    std::cout << "Controller input json:" << ss.str() << std::endl;

    /*
     *
     */
}

void GameController::addPlayer(std::string username) {

}

GameController::GameController(const GameController &other) {

}

GameController::GameController() {

}
