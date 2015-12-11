//
// Created by wiktor on 11.12.15.
//

#include <iostream>
#include "Observer.h"

using namespace std;

Observer::Observer(JNIInstance *jniI) {
    jniInstance = jniI;
}

void Observer::listen(int a) {
    jclass mgc = jniInstance->env->FindClass("to2/ds/game/controllers/MockedGameController");  // try to find the class
    jclass observer = jniInstance->env->FindClass("to2/ds/game/controllers/ObserverImpl");  // try to find the class
    jmethodID observerConstructor= jniInstance->env->GetMethodID(observer, "<init>", "(I)V");
    jobject observerObj = jniInstance->env->NewObject(observer, observerConstructor, a);
    jmethodID mgcConstructor= jniInstance->env->GetMethodID(mgc, "<init>", "(Lto2/ds/game/controllers/ObserverImpl;)V");
    jobject mgcObj = jniInstance->env->NewObject(mgc, mgcConstructor, observerObj);
    if(mgc == nullptr || observer== nullptr || mgcConstructor == nullptr || observerObj == nullptr ||mgcObj == nullptr) {
//    if(mgc == nullptr) {
        jniInstance->env->ExceptionDescribe();
        std::cerr << "ERROR: class not found !";
    }
    else {                                  // if class found, continue
        std::cout << "Class Main found" << std::endl;
        jmethodID mid = jniInstance->env->GetStaticMethodID(mgc, "startGameController", "(Lto2/ds/game/controllers/MockedGameController;)V");  // find method

        if(mgc == nullptr)
            std::cerr << "ERROR: method void mymain() not found !" << std::endl;
        else {
//            jobjectArray arr = jniInstance->env->NewObjectArray(5,      // constructs java array of 5
//                                                                jniInstance->env->FindClass("java/lang/String"),    // Strings
//                                                                jniInstance->env->NewStringUTF("str"));   // each initialized with value "str"


//            jniInstance->env->SetObjectArrayElement( arr, 0, jniInstance->env->NewStringUTF("/home/wiktor/Documents/try_jni"));  // change an element

            jniInstance->env->CallStaticVoidMethod(mgc, mid, mgcObj);// call method
            jmethodID notify = jniInstance->env->GetMethodID(observer, "notifyWaitUntil", "()V");
            jmethodID lastOp = jniInstance->env->GetMethodID(observer, "getLastOperation", "()Ljava/lang/String;");
            int i = 9;
            while (i > 0) {
                jniInstance->env->CallObjectMethod(observerObj, notify, "");
                jstring string = (jstring) jniInstance->env->CallObjectMethod(observerObj, lastOp, "");
                const char *str = jniInstance->env->GetStringUTFChars(string, 0);
                cout << str;
                flush(cout);
                jniInstance->env->ReleaseStringUTFChars(string, str);
                i--;
            }
            std::cout << "SUCCES" << std::endl;
        }
    }
}