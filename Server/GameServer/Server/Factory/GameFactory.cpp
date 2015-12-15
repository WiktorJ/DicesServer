//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameFactory.h"
#include "jni.h"
GameInstance *GameFactory::createGame(boost::property_tree::ptree description, WaitingRoom& WaitingRoom_) {
    JNIEnv *local_env;
    JNIInstance::getInstance().jvm->AttachCurrentThread((void **) &local_env, NULL);
    jclass mockedGameControllerClass = local_env->FindClass("to2/ds/game/controllers/MockedGameController");  // try to find the class
    jclass observerClass = local_env->FindClass("to2/ds/game/controllers/ObserverImpl");  // try to find the class
    jobject observerObj = local_env->AllocObject(observerClass);

    jmethodID mockedGameControllerConstructor = local_env->GetMethodID(mockedGameControllerClass, "<init>",
                                                                                            "(Lto2/ds/game/controllers/ObserverImpl;)V");
    jobject mockedGameControllerObj = local_env->NewObject(mockedGameControllerClass,
                                                                                mockedGameControllerConstructor, observerObj);

    jmethodID createGameController = local_env->GetStaticMethodID(mockedGameControllerClass, "startGameController",
                                                                                       "(Lto2/ds/game/controllers/MockedGameController;)V");  // find method

    local_env->CallStaticVoidMethod(mockedGameControllerClass, createGameController, mockedGameControllerObj);// call method

    return new GameInstance(new GameController(mockedGameControllerObj), WaitingRoom_, curr_id++, observerObj);
}

GameFactory::GameFactory() {
    curr_id = 0;
}
