//
// Created by Wojciech Grabis on 17.11.15.
//

#include <jni.h>
#include <stdlib.h>
#include <iostream>
#include "SimpleInstanceJNI.h"


SimpleInstanceJNI::SimpleInstanceJNI() {

    JavaVMInitArgs vm_args;                        // Initialization arguments
    JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options

    options[0].optionString =(char *) "-Djava.class.path=/home/wiktor/ClionProjects/DicesServer/JavaTest/out/production/JavaTest/.";   // where to find java .class

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

void SimpleInstanceJNI::close(){
    jvm->DestroyJavaVM();
}

void SimpleInstanceJNI::runSimpleWriter(const char* fileName) {
    jclass cls2 = env->FindClass("Main");  // try to find the class
    if(cls2 == nullptr) {
        env->ExceptionDescribe();
        std::cerr << "ERROR: class not found !";
    }
    else {                                  // if class found, continue
        std::cout << "Class Main found" << std::endl;
        jmethodID mid = env->GetStaticMethodID(cls2, "main", "([Ljava/lang/String;)V");  // find method

        if(mid == nullptr)
            std::cerr << "ERROR: method void mymain() not found !" << std::endl;
        else {
                jobjectArray arr = env->NewObjectArray(5,      // constructs java array of 5
                                                       env->FindClass("java/lang/String"),    // Strings
                                                       env->NewStringUTF("str"));   // each initialized with value "str"
                env->SetObjectArrayElement( arr, 0, env->NewStringUTF(fileName));  // change an element

            env->CallStaticVoidMethod(cls2, mid, arr);                      // call method
            std::cout << "SUCCES" << std::endl;
        }
    }
}