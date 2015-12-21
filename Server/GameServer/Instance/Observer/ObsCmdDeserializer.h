//
// Created by Wojciech Grabis on 16.12.15.
//

#ifndef DICESSERVER_OBSCMDDESERIALIZER_H
#define DICESSERVER_OBSCMDDESERIALIZER_H

#include <string>
#include <boost/property_tree/ptree.hpp>

class ObsCmdDeserializer {
public:
    static std::string deserialize(boost::property_tree::ptree &data);
    static std::string deserializeNick(boost::property_tree::ptree data);
};


#endif //DICESSERVER_OBSCMDDESERIALIZER_H
