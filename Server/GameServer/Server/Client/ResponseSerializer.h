//
// Created by wg on 08.01.16.
//

#ifndef DICESSERVER_RESPONSESERIALIZER_H
#define DICESSERVER_RESPONSESERIALIZER_H


#include <boost/property_tree/ptree_fwd.hpp>

class ResponseSerializer {
public:
    static boost::property_tree::ptree getPositiveResponse(std::string command, std::string data);
    static boost::property_tree::ptree getNegativeResponse(std::string command, std::string data);
};


#endif //DICESSERVER_RESPONSESERIALIZER_H
