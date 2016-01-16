//
// Created by wg on 16.01.16.
//

#ifndef DICESSERVER_CLIENTNOTFOUNDEXCEPTION_H
#define DICESSERVER_CLIENTNOTFOUNDEXCEPTION_H


#include <exception>

class ClientNotFoundException : public std::bad_exception{
public:
    virtual const char* what() const noexcept;
};


#endif //DICESSERVER_CLIENTNOTFOUNDEXCEPTION_H
