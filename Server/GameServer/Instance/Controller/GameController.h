//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMECONTROLLER_H
#define DICESSERVER_GAMECONTROLLER_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include "jni.h"

//TODO CONNECT WITH JAVA
class GameController {
private:
    jobject javaGameController;
    JNIEnv * localEnv;
public:
    GameController(const GameController &other);
    GameController(jobject jgc);
    GameController();
    void addPlayer(std::string username);
    void makeMove(boost::property_tree::ptree moveInfo);
    void removePlayer(std::string username);
    boost::property_tree::ptree getGameInfo();

    void setLocalEnvy(JNIEnv *jniEnv);
};


#endif //DICESSERVER_GAMECONTROLLER_H
