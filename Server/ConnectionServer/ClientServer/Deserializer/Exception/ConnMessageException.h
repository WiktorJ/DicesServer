//
// Created by wg on 17.01.16.
//

#ifndef DICESSERVER_CONNMESSAGEEXCEPTION_H
#define DICESSERVER_CONNMESSAGEEXCEPTION_H


#include <exception>

class ConnMessageException : public std::bad_exception{
public:
    virtual const char* what() const noexcept;
};


#endif //DICESSERVER_CONNMESSAGEEXCEPTION_H
