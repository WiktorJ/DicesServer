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
    LogParser Logger;
    jobject Object;

    void initialize();
public:
    JObserver();
    void attach(JNIEnv* Env);
    std::string notify();
    bool isFinished();
    jobject& getObject();
};


#endif //DICESSERVER_JOBSERVER_H
