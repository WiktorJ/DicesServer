//
// Created by Wojciech Grabis on 16.12.15.
//

#ifndef DICESSERVER_JCONTROLLER_H
#define DICESSERVER_JCONTROLLER_H


#include <jni.h>
#include <string>
#include "../../../../Logger/LogParser.h"

class JController {
private:
    JNIEnv* Env;
    jobject Object;
    jclass Controller;

    jmethodID AddPlayer;
    jmethodID RemovePlayer;
    jmethodID MakeMove;
    jmethodID Stop;
    jmethodID GetGameInfo;

    LogParser Logger;

    void initialize();
public:
    JController(jobject Object, JNIEnv* Env);
    void attach(JNIEnv* Env);

    void addPlayer(std::string username);
    void removePlayer(std::string username);
    void makeMove(std::string move);
    void stop();
    std::string getGameInfo();
};


#endif //DICESSERVER_JCONTROLLER_H
