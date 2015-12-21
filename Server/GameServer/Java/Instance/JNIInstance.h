//
// Created by wiktor on 11.12.15.
//

#ifndef DICESSERVER_JNIINSTANCE_H
#define DICESSERVER_JNIINSTANCE_H

#include <boost/thread/pthread/mutex.hpp>
#include "jni.h"
#include "../../../Logger/LogParser.h"


class JNIInstance {
private:
    JNIInstance();
    ~JNIInstance();

    LogParser Logger;
    JavaVM *jvm;
    JNIEnv *env;
    boost::mutex Mutex;
public:
    static JNIInstance& getInstance();
    JNIEnv* attacheThread();

};

#endif //DICESSERVER_JNIINSTANCE_H
