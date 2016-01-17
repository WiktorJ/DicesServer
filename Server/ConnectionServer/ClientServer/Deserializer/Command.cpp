//
// Created by wg on 17.01.16.
//

#include "Command.h"

Command::Command(std::string command) {
    if(command == "addClient") Command_ = ConnCommand::ADDPLAYER;
    else if(command == "removeClient") Command_ = ConnCommand::REMOVEPLAYER;
    else if(command == "quit") Command_ = ConnCommand::QUIT;
    else if(command == "request") Command_ = ConnCommand::REQUEST;
    else Command_ = ConnCommand::UNKNOWN;
}

ConnCommand Command::getCommand() {
    return Command_;
}
