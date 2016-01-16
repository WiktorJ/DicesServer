//
// Created by wg on 16.01.16.
//

#include "ClientNotFoundException.h"

const char *ClientNotFoundException::what() const noexcept{
    return "Client not found";
}
