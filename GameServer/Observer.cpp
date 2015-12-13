//
// Created by wiktor on 11.12.15.
//

#include <iostream>
#include "Observer.h"
#include "jni.h"

using namespace std;

Observer::Observer(JNIInstance *jniI) {
    jniInstance = jniI;
}

void Observer::listen(int a) {
    JNIEnv *local_env;
    jniInstance->jvm->AttachCurrentThread((void **) &local_env, NULL);

    jclass mgc = local_env->FindClass("to2/ds/game/controllers/MockedGameController");  // try to find the class
    jclass observer = local_env->FindClass("to2/ds/game/controllers/ObserverImpl");  // try to find the class
    jmethodID observerConstructor = local_env->GetMethodID(observer, "<init>", "(I)V");
    jobject observerObj = local_env->NewObject(observer, observerConstructor, a);
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
        jmethodID notify = local_env->GetMethodID(observer, "notifyWaitUntil", "()V");
        jmethodID lastOp = local_env->GetMethodID(observer, "getLastOperation", "()Ljava/lang/String;");
        int i = 9;
        while (i > 0) {
            local_env->CallObjectMethod(observerObj, notify, "");
            jstring string = (jstring) local_env->CallObjectMethod(observerObj, lastOp, "");
            const char *str = local_env->GetStringUTFChars(string, 0);
            cout << str;
            flush(cout);
            local_env->ReleaseStringUTFChars(string, str);
            i--;
        }
        std::cout << "SUCCES" << std::endl;

    }
}