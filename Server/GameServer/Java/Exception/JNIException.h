//
// Created by Wojciech Grabis on 16.12.15.
//

#ifndef DICESSERVER_JNIEXCEPTION_H
#define DICESSERVER_JNIEXCEPTION_H


#include <exception>

class JNIException : std::exception{
public:
    virtual const char* what() const noexcept;
};


#endif //DICESSERVER_JNIEXCEPTION_H
