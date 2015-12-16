//
// Created by Wojciech Grabis on 16.12.15.
//

#include "JNIException.h"

const char *JNIException::what() const noexcept{
    return "JNI Error";
}
