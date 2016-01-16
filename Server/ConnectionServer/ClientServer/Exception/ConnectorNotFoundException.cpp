//
// Created by wg on 16.01.16.
//

#include "ConnectorNotFoundException.h"

const char *ConnectorNotFoundException::what() const noexcept{
    return "Connector not found";
}