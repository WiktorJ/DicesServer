//
// Created by Wojciech Grabis on 16.12.15.
//

#ifndef DICESSERVER_JFACTORY_H
#define DICESSERVER_JFACTORY_H


#include <jni.h>
#include "../Controller/JController.h"
#include "../Observer/JObserver.h"

class JFactory {
private:
    JNIEnv* Env;
    LogParser Logger;
    jmethodID Create;
    jclass Factory;

    void initialize();
public:
    JFactory();
    JController createGame(std::string description, JObserver observer);
    void attach(JNIEnv* Env);
};


#endif //DICESSERVER_JFACTORY_H
