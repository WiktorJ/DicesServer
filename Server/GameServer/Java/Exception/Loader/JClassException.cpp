//
// Created by Wojciech Grabis on 16.12.15.
//

#include "JClassException.h"

const char *JClassException::what() const noexcept{
    return std::string("Java class " + className + "or method not found").c_str();
}

JClassException::JClassException(std::string className) : className(className){

}
