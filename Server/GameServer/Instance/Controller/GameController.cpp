//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameController.h"
#include <boost/property_tree/json_parser.hpp>

boost::property_tree::ptree GameController::getGameInfo() {
    jclass gc = localEnv->FindClass("to2/ds/game/controllers/Game");  // try to find the class
    jmethodID makeMoveMethod = localEnv->GetMethodID(gc, "getInfo", "()Ljava/lang/String;");
    localEnv->CallVoidMethod(javaGameController, makeMoveMethod, "");

}

void GameController::removePlayer(std::string username) {

}

void GameController::makeMove(boost::property_tree::ptree moveInfo) {
    /* temporary
     *
     */
    std::stringstream ss;
    boost::property_tree::write_json(ss, moveInfo);

    std::cout << "Controller input json:" << ss.str() << std::endl;

    jclass gc = localEnv->FindClass("to2/ds/game/controllers/Game");  // try to find the class
    jmethodID makeMoveMethod = localEnv->GetMethodID(gc, "makeMove", "(Ljava/lang/String;)V");
    localEnv->CallVoidMethod(javaGameController, makeMoveMethod, ss.str().c_str());

    /*
     *
     */
}

void GameController::addPlayer(std::string username) {
    jclass gc = localEnv->FindClass("to2/ds/game/controllers/Game");  // try to find the class
    jmethodID addPlayerMethod = localEnv->GetMethodID(gc, "addPlayer", "(Ljava/lang/String;)V");
    localEnv->CallVoidMethod(javaGameController, addPlayerMethod, username.c_str());

    std::cout << "Wykonanie" << std::endl;
}

GameController::GameController(const GameController &other) {

}

GameController::GameController() {

}

GameController::GameController(jobject jgc) {
    javaGameController = jgc;
}

void GameController::setLocalEnvy(JNIEnv *jniEnv) {
    localEnv = jniEnv;
}
