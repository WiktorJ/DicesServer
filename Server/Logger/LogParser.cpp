//
// Created by Wojciech Grabis on 15.12.15.
//

#include "LogParser.h"
#include "Logger.h"

LogParser::LogParser(std::string className) {
    Prefix = "[Object : " + className + " " + std::to_string(Logger::getInstance().getId()) +  "]";
}

void LogParser::log(std::string info) {
    Logger::getInstance().log(Prefix + " -> " + info + "  ");
}
