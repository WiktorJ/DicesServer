//
// Created by Wojciech Grabis on 16.12.15.
//

#include "JFactory.h"
#include "../../Exception/Env/JNIEnvException.h"
#include "../../Exception/Loader/JClassException.h"
#include "../../Instance/JConfig.h"

JFactory::JFactory(JNIEnv* Env) : Logger("JFactory"){
    this->Env = Env;

    initialize();

    this->Env = NULL;
}

void JFactory::attach(JNIEnv *Env) {
    this->Env = Env;
}

JController JFactory::createGame(std::string description, JObserver observer) {
    Logger.log("Creating new controller");
    if(Env == NULL)throw new JNIEnvException;

    jstring desc = Env->NewStringUTF(description.c_str());
    Logger.log(description);

    jobject Controller = Env->CallStaticObjectMethod(Factory, Create, desc, observer.getObject());

    if (Env->ExceptionCheck()){
        Env->ExceptionDescribe();
        Env->ExceptionClear();
        Logger.log("Game could not be created");
        throw new JNIException;
    }

    JController controller(Controller, Env);

    return controller;
}

void JFactory::initialize() {
    Logger.log("Initializing");


    //TODO CONNECT TO A JAVA CONFIG
    const char* temp = JConfig::getInstance().getFactoryPackage().c_str();
    std::string tempstr = (std::string("(Ljava/lang/String;L") + JConfig::getInstance().getObserverPackage() + std::string(";)L") + JConfig::getInstance().getControllerPackage() + std::string(";"));
    const char* temp_controller = tempstr.c_str();

    Factory = Env->FindClass(temp);
    Create = Env->GetStaticMethodID(Factory , "createGame", temp_controller);

    if(Factory == 0 || Create == 0){
        Logger.log(std::string("Failed to init jfactory ") + temp + " " + std::to_string(Factory == 0) + " " + temp_controller + " " + std::to_string(Create == 0));
        throw new JClassException("JFactory");
    }

}