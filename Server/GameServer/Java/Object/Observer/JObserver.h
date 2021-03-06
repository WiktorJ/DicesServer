//
// Created by Wojciech Grabis on 16.12.15.
//

#ifndef DICESSERVER_JOBSERVER_H
#define DICESSERVER_JOBSERVER_H


#include <jni.h>
#include "../../../../Logger/LogParser.h"

class JObserver {
private:
    JNIEnv* Env;
    jclass Observer;
    jmethodID Notify;
    jmethodID IsGameEnded;
    jmethodID Constructor;
    LogParser Logger;
    jobject Object;

    void initialize();
public:
    JObserver(JNIEnv* Env);
    void attach(JNIEnv* Env);
    std::string notify();
    bool isFinished();
    jobject& getObject();
    void create();
};


#endif //DICESSERVER_JOBSERVER_H
