//
// Created by Wojciech Grabis on 14.12.15.
//

#ifndef DICESSERVER_MAINSERVER_H
#define DICESSERVER_MAINSERVER_H


#include "../GameServer/Server/GameServer.h"

class MainServer {
private:
    GameServer* GameServer_;
    LogParser Logger;
    bool state;
    ConnectionServer* connectionServer;

public:
    MainServer();
    ~MainServer();
    std::string printGameInfo();
    void start();
    void stop();

    void temporaryClient(Client* test);
};


#endif //DICESSERVER_MAINSERVER_H
