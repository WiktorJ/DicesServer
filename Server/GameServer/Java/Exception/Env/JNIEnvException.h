//
// Created by Wojciech Grabis on 16.12.15.
//

#ifndef DICESSERVER_JNIENVEXCEPTION_H
#define DICESSERVER_JNIENVEXCEPTION_H


#include <exception>
#include "../JNIException.h"

class JNIEnvException : JNIException{
    const char* what() const noexcept;

};


#endif //DICESSERVER_JNIENVEXCEPTION_H
