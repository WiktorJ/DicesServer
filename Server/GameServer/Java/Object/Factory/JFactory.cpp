//
// Created by Wojciech Grabis on 16.12.15.
//

#include "JFactory.h"
#include "../../Exception/Env/JNIEnvException.h"

JFactory::JFactory() : Logger("JFactory"){
    Env = NULL;
}

void JFactory::attach(JNIEnv *Env) {
    this->Env = Env;

    initialize();
}

JController JFactory::createGame(std::string description, JObserver observer) {
    Logger.log("Creating new controller");
    if(Env == NULL)throw new JNIEnvException;

    jobject Controller = Env->CallStaticObjectMethod(Factory, Create, observer.getObject());

    JController controller(Controller);

    return controller;
}

void JFactory::initialize() {
    Logger.log("Initializing");


    //TODO CONNECT TO A JAVA CONFIG
    const char* temp = "to2/ds/game/controllers/GameFactory";
    const char* temp_controller = "(Ljava/lang/String;Lto2/ds/game/controllers/ObserverImpl;)Lto2/ds/game/controllers/GameController;";

    Factory = Env->FindClass(temp);
    Create = Env->GetStaticMethodID(Factory , "createGame", temp_controller);

}
