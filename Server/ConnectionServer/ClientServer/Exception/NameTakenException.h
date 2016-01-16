//
// Created by wg on 16.01.16.
//

#ifndef DICESSERVER_NAMETAKENEXCEPTION_H
#define DICESSERVER_NAMETAKENEXCEPTION_H


#include <exception>

class NameTakenException : public std::bad_exception{
public:
    virtual const char* what() const noexcept;
};


#endif //DICESSERVER_NAMETAKENEXCEPTION_H
