//
// Created by Wojciech Grabis on 16.12.15.
//

#include "JNIEnvException.h"

const char *JNIEnvException::what() const noexcept{
    return "JNI Env variable not set correctly";
}
