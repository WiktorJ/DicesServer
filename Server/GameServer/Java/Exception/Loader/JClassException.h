//
// Created by Wojciech Grabis on 16.12.15.
//

#ifndef DICESSERVER_JCLASSEXCEPTION_H
#define DICESSERVER_JCLASSEXCEPTION_H


#include "../JNIException.h"
#include <string>

class JClassException : JNIException{
private:
    std::string className;
public:
    JClassException(std::string className);
    virtual const char* what() const noexcept;
};


#endif //DICESSERVER_JCLASSEXCEPTION_H
