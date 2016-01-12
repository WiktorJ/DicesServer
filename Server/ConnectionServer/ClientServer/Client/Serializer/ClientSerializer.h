//
// Created by wg on 12.01.16.
//

#ifndef DICESSERVER_CLIENTSERIALIZER_H
#define DICESSERVER_CLIENTSERIALIZER_H


#include <boost/property_tree/ptree.hpp>

class ClientSerializer {
public:
    static boost::property_tree::ptree serializeUserName(std::string ClientName, boost::property_tree::ptree data);
    static boost::property_tree::ptree serializeType(boost::property_tree::ptree data);
};


#endif //DICESSERVER_CLIENTSERIALIZER_H
