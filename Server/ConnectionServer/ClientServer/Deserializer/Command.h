//
// Created by wg on 17.01.16.
//

#ifndef DICESSERVER_COMMAND_H
#define DICESSERVER_COMMAND_H

#include <string>

enum ConnCommand{
    QUIT,
    REQUEST,
    ADDPLAYER,
    REMOVEPLAYER,
    UNKNOWN
};

class Command {
private:
    ConnCommand Command_;
public:
    Command(std::string command);
    ConnCommand getCommand();
};


#endif //DICESSERVER_COMMAND_H
