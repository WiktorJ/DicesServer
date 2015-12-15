//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameFactory.h"
#include "jni.h"
GameInstance *GameFactory::createGame(boost::property_tree::ptree description, WaitingRoom& WaitingRoom_) {
    jclass mockedGameControllerClass = JNIInstance::getInstance().env->FindClass("to2/ds/game/controllers/MockedGameController");  // try to find the class
    jclass observerClass = JNIInstance::getInstance().env->FindClass("to2/ds/game/controllers/ObserverImpl");  // try to find the class
    jobject observerObj = JNIInstance::getInstance().env->AllocObject(observerClass);

    jmethodID mockedGameControllerConstructor = JNIInstance::getInstance().env->GetMethodID(mockedGameControllerClass, "<init>",
                                                                                            "(Lto2/ds/game/controllers/ObserverImpl;)V");
    jobject mockedGameControllerObj = JNIInstance::getInstance().env->NewObject(mockedGameControllerClass,
                                                                                mockedGameControllerConstructor, observerObj);

    jmethodID createGameController = JNIInstance::getInstance().env->GetStaticMethodID(mockedGameControllerClass, "startGameController",
                                                                                       "(Lto2/ds/game/controllers/MockedGameController;)V");  // find method

    JNIInstance::getInstance().env->CallStaticVoidMethod(mockedGameControllerClass, createGameController, mockedGameControllerObj);// call method

    return new GameInstance(new GameController(mockedGameControllerObj), WaitingRoom_, curr_id++, mockedGameControllerObj);
}

GameFactory::GameFactory() {
    curr_id = 0;
}
