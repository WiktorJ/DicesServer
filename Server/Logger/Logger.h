//
// Created by Wojciech Grabis on 15.12.15.
//

#ifndef DICESSERVER_LOGGER_H
#define DICESSERVER_LOGGER_H

#include <string>

class Logger {
private:
    Logger();
    ~Logger();

    int id;
public:
    static Logger & getInstance();
    int getId();
    void log(std::string logInfo);
};


#endif //DICESSERVER_LOGGER_H
