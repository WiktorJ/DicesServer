//
// Created by Wojciech Grabis on 13.12.15.
//

#include "Observer.h"
#include "JNIInstance.cpp"

using namespace std;

Observer::Observer(ClientGroup& Clients) : Clients(Clients){

}

void Observer::listen() {
    bool gameEnded = false;
    JNIEnv *local_env;
    JNIInstance::getInstance().jvm->AttachCurrentThread((void **) &local_env, NULL);
    jclass mgc = local_env->FindClass("to2/ds/game/controllers/MockedGameController");  // try to find the class
    jclass observer = local_env->FindClass("to2/ds/game/controllers/ObserverImpl");  // try to find the class
    jobject observerObj = local_env->AllocObject(observer);
    jmethodID mgcConstructor = local_env->GetMethodID(mgc, "<init>", "(Lto2/ds/game/controllers/ObserverImpl;)V");
    jobject mgcObj = local_env->NewObject(mgc, mgcConstructor, observerObj);
    if (mgc == nullptr || observer == nullptr || mgcConstructor == nullptr || observerObj == nullptr ||
        mgcObj == nullptr) {
        local_env->ExceptionDescribe();
        std::cerr << "ERROR: class not found !";
    }
    else {                                  // if class found, continue
        std::cout << "Class Main found" << std::endl;
        jmethodID mid = local_env->GetStaticMethodID(mgc, "startGameController",
                                                     "(Lto2/ds/game/controllers/MockedGameController;)V");  // find method

        local_env->CallStaticVoidMethod(mgc, mid, mgcObj);// call method
        jmethodID notify = local_env->GetMethodID(observer, "notifyWaitUntil", "()Ljava/lang/String;");
        jmethodID isGameEnded = local_env->GetMethodID(observer, "isGameEnded", "()Z");
        while (!gameEnded) {
            jstring string = (jstring) local_env->CallObjectMethod(observerObj, notify, "");
            jboolean javaBoolean = local_env->CallBooleanMethod(observerObj, isGameEnded, "");
            gameEnded = (bool)(javaBoolean == JNI_TRUE);
            const char *str = local_env->GetStringUTFChars(string, 0);
            cout << str;
            flush(cout);
            local_env->ReleaseStringUTFChars(string, str);
        }
        std::cout << "SUCCES" << std::endl;

    }
}
