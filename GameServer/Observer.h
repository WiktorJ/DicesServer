//
// Created by wiktor on 11.12.15.
//

#ifndef DICESSERVER_OBSERVER_H
#define DICESSERVER_OBSERVER_H




class SimpleInstanceJNI {
private:
    JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
    JNIEnv *env;                      // Pointer to native interface
public:
    SimpleInstanceJNI();
    void close();
    void runSimpleWriter(const char* fileName);
};




#endif //DICESSERVER_OBSERVER_H
