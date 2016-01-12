//
// Created by wg on 12.01.16.
//

#ifndef DICESSERVER_GAMERESPONSESERIALIZER_H
#define DICESSERVER_GAMERESPONSESERIALIZER_H


#include <boost/property_tree/ptree.hpp>

enum status{
    FAILURE,
    SUCCESS
};

class GameResponseSerializer {
public:
    static boost::property_tree::ptree serializeResponse(std::string command, status Status, boost::property_tree::ptree data);
};


#endif //DICESSERVER_GAMERESPONSESERIALIZER_H
