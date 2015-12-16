//
// Created by Wojciech Grabis on 16.12.15.
//

#include "JObserver.h"
#include "../../Exception/Env/JNIEnvException.h"
#include "../../Exception/Loader/JClassException.h"

void JObserver::attach(JNIEnv *Env) {
    this->Env = Env;
}

JObserver::JObserver() : Object(), Logger("JObserver"){
    Env = NULL;
}

void JObserver::initialize() {
    Logger.log("Initializing java object");

    //TODO CONNECT TO A JAVA CONFIG
    const char* temp = "to2/ds/game/controllers/ObserverImpl";

    Observer = Env->FindClass(temp);

    Notify = Env->GetMethodID(Observer, "notifyWaitUntil", "()Ljava/lang/String;");
    IsGameEnded = Env->GetMethodID(Observer, "isGameEnded", "()Z");

    if(Observer == NULL || Notify == NULL || IsGameEnded == NULL) throw new JClassException("Observer");

    Object = Env->AllocObject(Observer);
}

std::string JObserver::notify() {
    if(Env == NULL)throw new JNIEnvException;

    jstring Result = (jstring) Env->CallObjectMethod(Object, Notify, "");
    const char *str = Env->GetStringUTFChars(Result, 0);

    std::string Converted = std::string(str);
    Env->ReleaseStringUTFChars(Result, str);

    return Converted;
}

bool JObserver::isFinished() {
    if(Env == NULL)throw new JNIEnvException;

    jboolean GameState = Env->CallBooleanMethod(Object, IsGameEnded, "");
    bool gameEnded = (GameState == JNI_TRUE);

    return gameEnded;
}

jobject &JObserver::getObject() {
    return Object;
}
