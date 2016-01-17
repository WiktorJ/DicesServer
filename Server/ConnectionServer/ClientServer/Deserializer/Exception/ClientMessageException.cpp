//
// Created by wg on 17.01.16.
//

#include "ClientMessageException.h"

const char *ClientMessageException::what() const noexcept{
    return "Client not found";
}