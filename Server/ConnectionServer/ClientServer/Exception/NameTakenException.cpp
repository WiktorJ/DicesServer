//
// Created by wg on 16.01.16.
//

#include "NameTakenException.h"

const char *NameTakenException::what() const noexcept{
    return "Name taken";
}