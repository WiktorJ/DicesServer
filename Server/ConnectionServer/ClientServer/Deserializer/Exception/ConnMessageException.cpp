//
// Created by wg on 17.01.16.
//

#include "ConnMessageException.h"

const char *ConnMessageException::what() const noexcept{
    return "Client not found";
}