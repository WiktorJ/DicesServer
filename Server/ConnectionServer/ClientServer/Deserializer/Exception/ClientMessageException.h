//
// Created by wg on 17.01.16.
//

#ifndef DICESSERVER_CLIENTMESSAGEEXCEPTION_H
#define DICESSERVER_CLIENTMESSAGEEXCEPTION_H


#include <exception>

class ClientMessageException : public std::bad_exception{
public:
    virtual const char* what() const noexcept;
};


#endif //DICESSERVER_CLIENTMESSAGEEXCEPTION_H
