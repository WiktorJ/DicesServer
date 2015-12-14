//
// Created by wiktor on 11.12.15.
//
#include <jni.h>
#include <stdlib.h>
#include <iostream>
#include "JNIInstance.h"


JNIInstance::JNIInstance()  {

    JavaVMInitArgs vm_args;                        // Initialization arguments
    JavaVMOption* options = new JavaVMOption[2];   // JVM invocation options

    options[0].optionString =(char *) "-Djava.class.path=/home/wiktor/ClionProjects/DicesServer/ControllersContainer/target/classes/.:/home/wiktor/ClionProjects/DicesServer/ControllersContainer/target/lib/json-20151123.jar";   // where to find java .class
    vm_args.version = JNI_VERSION_1_6;             // minimum Java version
    vm_args.nOptions = 1;                          // number of options
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail

    jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!

    delete options;    // we then no longer need the initialisation options.

    if (rc != JNI_OK) {
        throw "Zjebane JVM";
    }

    std::cout << "JVM load succeeded: Version ";
    jint ver = env->GetVersion();
    std::cout << ((ver>>16)&0x0f) << "."<<(ver&0x0f) << std::endl;
}

JNIInstance& JNIInstance::getInstance() {
        static JNIInstance instance;
        return instance;
}

JNIInstance::~JNIInstance() {
    jvm->DestroyJavaVM();
}