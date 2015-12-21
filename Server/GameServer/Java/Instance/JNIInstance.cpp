//
// Created by wiktor on 11.12.15.
//
#include <jni.h>
#include <stdlib.h>
#include <iostream>
#include "JNIInstance.h"
#include "../Exception/JNIException.h"
#include "JConfig.h"


JNIInstance::JNIInstance()  : Logger("JNIInstance"){

    JavaVMInitArgs vm_args;                        // Initialization arguments
    JavaVMOption* options = new JavaVMOption[2];   // JVM invocation options
//Djava.class.path
    std::string tempstr = ("-Djava.class.path=" + JConfig::getInstance().getJarPath());
    const char * jarPath = tempstr.c_str();
    std::cout << jarPath << std::endl;

    options[0].optionString = const_cast<char*>(jarPath);

//    options[0].optionString = ("-Djava.class.path=/Users/wgrabis/ClionProjects/DicesServer/TestJson/Controller/.");   // where to find java .class
    vm_args.version = JNI_VERSION_1_6;             // minimum Java version
    vm_args.nOptions = 1;                          // number of options
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;     // invalid options make the JVM init fail

    jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!

    delete options;    // we then no longer need the initialisation options.

    if (rc != JNI_OK) {
        throw new JNIException;
    }

    jint ver = env->GetVersion();
    Logger.log("JVM load succeeded: Version " + std::to_string((ver>>16)&0x0f) + "." + std::to_string(ver&0x0f));
}

JNIInstance& JNIInstance::getInstance() {
        static JNIInstance instance;
        return instance;
}

JNIInstance::~JNIInstance() {
    Logger.log("Destroying JVM");
    jvm->DestroyJavaVM();
}

JNIEnv* JNIInstance::attacheThread() {
    Mutex.lock();

    Logger.log("Attaching new thread");
    JNIEnv *localEnv;
    JNIInstance::getInstance().jvm->AttachCurrentThread((void **) &localEnv, NULL);

    Mutex.unlock();
    return localEnv;
}
