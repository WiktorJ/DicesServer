//
// Created by wg on 16.01.16.
//

#ifndef DICESSERVER_CONNECTORNOTFOUNDEXCEPTION_H
#define DICESSERVER_CONNECTORNOTFOUNDEXCEPTION_H


#include <exception>

class ConnectorNotFoundException : public std::bad_exception {
public:
    virtual const char* what() const noexcept;
};


#endif //DICESSERVER_CONNECTORNOTFOUNDEXCEPTION_H
