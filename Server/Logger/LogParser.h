//
// Created by Wojciech Grabis on 15.12.15.
//

#ifndef DICESSERVER_LOGPARSER_H
#define DICESSERVER_LOGPARSER_H


#include <string>

class LogParser {
private:
    std::string Prefix;
public:
    LogParser(std::string className);
    void log(std::string info);
};


#endif //DICESSERVER_LOGPARSER_H
