//
// Created by Wojciech Grabis on 16.12.15.
//

#include "JController.h"
#include "../../Exception/Loader/JClassException.h"
#include "../../Exception/Env/JNIEnvException.h"
#include "../../Instance/JConfig.h"

JController::JController(jobject Object, JNIEnv* Env) : Logger("JController"), Object(Object){
    this->Env = Env;

    initialize();

    this->Env = NULL;
}

void JController::attach(JNIEnv *Env) {
    this->Env = Env;
}

void JController::initialize() {
    Logger.log("Initializing java object");

    //TODO CONNECT TO A JAVA CONFIG
    const char* temp = JConfig::getInstance().getControllerPackage().c_str();

    Controller = Env->FindClass(temp);

    AddPlayer = Env->GetMethodID(Controller, "addPlayer", "(Ljava/lang/String;)V");
    RemovePlayer = Env->GetMethodID(Controller, "removePlayer", "(Ljava/lang/String;)V");
    MakeMove = Env->GetMethodID(Controller, "makeMove", "(Ljava/lang/String;)V");
    Stop = Env->GetMethodID(Controller, "stop", "()V");
    GetGameInfo = Env->GetMethodID(Controller, "getGameInfo", "()Ljava/lang/String;");

    if(Controller == 0 || AddPlayer == 0 || RemovePlayer == 0 || MakeMove == 0 || Stop == 0 || GetGameInfo == 0){
        Logger.log("Could not get running");
        throw new JClassException("Controller");
    }

}

void JController::addPlayer(std::string username) {
    if(Env == NULL)throw new JNIEnvException;

    Env->CallVoidMethod(Object, AddPlayer, username.c_str());
}

void JController::removePlayer(std::string username) {
    if(Env == NULL)throw new JNIEnvException;

    Env->CallVoidMethod(Object, RemovePlayer, username.c_str());
}

void JController::makeMove(std::string move) {
    if(Env == NULL)throw new JNIEnvException;

    Env->CallVoidMethod(Object, MakeMove, move.c_str());
}

void JController::stop() {
    if(Env == NULL)throw new JNIEnvException;

    Env->CallVoidMethod(Object, Stop);

}

std::string JController::getGameInfo(JNIEnv* TEnv) {
    if(TEnv == NULL)throw new JNIEnvException;

    jstring Result = (jstring) TEnv->CallObjectMethod(Object, GetGameInfo, "");
    const char *str = TEnv->GetStringUTFChars(Result, 0);

    std::string Converted = std::string(str);
    TEnv->ReleaseStringUTFChars(Result, str);

    return Converted;
}

