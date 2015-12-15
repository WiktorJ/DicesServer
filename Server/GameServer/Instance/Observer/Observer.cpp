//
// Created by Wojciech Grabis on 13.12.15.
//

#include "Observer.h"
#include "JNIInstance.cpp"

using namespace std;

Observer::Observer(ClientGroup &Clients, jobject gco) : Clients(Clients), Logger("Observer"){
    observerObject = gco;
}

void Observer::listen() {
    bool gameEnded = false;
    JNIEnv *localEnv;
    JNIInstance::getInstance().jvm->AttachCurrentThread((void **) &localEnv, NULL);

    // if class found, continue
    std::cout << "Class Main found" << std::endl;
    jclass observerClass = localEnv->FindClass("to2/ds/game/controllers/ObserverImpl");
    jmethodID notify = localEnv->GetMethodID(observerClass, "notifyWaitUntil", "()Ljava/lang/String;");
    jmethodID isGameEnded = localEnv->GetMethodID(observerClass, "isGameEnded", "()Z");
    while (!gameEnded) {
        jstring string = (jstring) localEnv->CallObjectMethod(observerObject, notify, "");
        jboolean javaBoolean = localEnv->CallBooleanMethod(observerObject, isGameEnded, "");
        gameEnded = (bool) (javaBoolean == JNI_TRUE);
        const char *str = localEnv->GetStringUTFChars(string, 0);
        cout << str;
        flush(cout);
        Clients.sendData(str);
        localEnv->ReleaseStringUTFChars(string, str);
    }
    Logger.log("listen finished");


}
