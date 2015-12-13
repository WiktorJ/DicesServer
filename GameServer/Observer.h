//
// Created by wiktor on 11.12.15.
//

#ifndef DICESSERVER_OBSERVER_H
#define DICESSERVER_OBSERVER_H


#include "JNIInstance.h"
#include "jni.h"
class Observer {
private:
    JNIInstance* jniInstance;
public:
    Observer(JNIInstance *jniI);
    void listen(int a);
    char* getMessage();

};




#endif //DICESSERVER_OBSERVER_H
