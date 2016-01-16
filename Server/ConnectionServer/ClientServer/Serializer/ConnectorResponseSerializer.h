//
// Created by wg on 16.01.16.
//

#ifndef DICESSERVER_CONNECTORRESPONSESERIALIZER_H
#define DICESSERVER_CONNECTORRESPONSESERIALIZER_H


#include <boost/property_tree/ptree.hpp>
#include "../../../GameServer/Instance/Client/GameResponseSerializer.h"

class ConnectorResponseSerializer {
public:
    static boost::property_tree::ptree serializeType(boost::property_tree::ptree response);
    static boost::property_tree::ptree serializeResponse(std::string command, status status_);
};


#endif //DICESSERVER_CONNECTORRESPONSESERIALIZER_H
