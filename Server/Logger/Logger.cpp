//
// Created by Wojciech Grabis on 15.12.15.
//

#include <iostream>
#include "Logger.h"

Logger &Logger::getInstance() {
    static Logger Logger_;

    return Logger_;
}

Logger::Logger() {
    id = 1;
}

Logger::~Logger() {

}

int Logger::getId() {
    return id++;
}

void Logger::log(std::string logInfo) {
    Mutex.lock();
    std::cout << logInfo << std::endl;
    Mutex.unlock();
}

