//
// Created by wiktor on 11.12.15.
//

#ifndef DICESSERVER_JNIINSTANCE_H
#define DICESSERVER_JNIINSTANCE_H

#include "jni.h"


class JNIInstance {
public:
    JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
    JNIEnv *env;
    JNIInstance(const char* pathToClass);
    void close();
    void runSimpleWriter(const char* fileName);
};

#endif //DICESSERVER_JNIINSTANCE_H
