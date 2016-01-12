//
// Created by wg on 12.01.16.
//

#ifndef DICESSERVER_CLIENTSERIALIZER_H
#define DICESSERVER_CLIENTSERIALIZER_H


#include <boost/property_tree/ptree.hpp>

class ClientSerializer {
public:
    static boost::property_tree::ptree serialize(std::string ClientName, boost::property_tree::ptree data, std::string command);
};


#endif //DICESSERVER_CLIENTSERIALIZER_H
