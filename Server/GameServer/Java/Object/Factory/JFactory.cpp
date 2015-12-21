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

    jobject Controller = Env->CallStaticObjectMethod(Factory, Create, description.c_str(), observer.getObject());

    JController controller(Controller, Env);

    return controller;
}

void JFactory::initialize() {
    Logger.log("Initializing");


    //TODO CONNECT TO A JAVA CONFIG
    const char* temp = JConfig::getInstance().getFactoryPackage().c_str();
    const char* temp_controller = ("(Ljava/lang/String;L" + JConfig::getInstance().getObserverPackage() + ";)L" + JConfig::getInstance().getControllerPackage() + ";").c_str();

    Factory = Env->FindClass(temp);
    Create = Env->GetStaticMethodID(Factory , "createGame", temp_controller);

    if(Factory == 0 || Create == 0){
        Logger.log("Failed to init jfactory " + std::to_string(Factory == 0) + " " + std::to_string(Create == 0));
        throw new JClassException("JFactory");
    }

}
