//
// Created by wiktor on 11.12.15.
//

#ifndef DICESSERVER_JNIINSTANCE_H
#define DICESSERVER_JNIINSTANCE_H

#include "jni.h"


class JNIInstance {
private:
    JNIInstance();
    ~JNIInstance();
//    JNIInstance(JNIInstance const&);
//    void operator=(JNIInstance const&);
public:
    static JNIInstance& getInstance();
    JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
    JNIEnv *env;

//    JNIInstance(JNIInstance const&) = delete;
//    void operator=(JNIInstance const&) = delete;
};

#endif //DICESSERVER_JNIINSTANCE_H
