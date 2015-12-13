//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_GAMEHOLDER_H
#define DICESSERVER_GAMEHOLDER_H


#include "../Instance/GameInstance.h"

class GameHolder {
private:
    std::vector<GameInstance *> Games;
    boost::mutex Mutex;
    void update();
public:
    GameHolder();
    ~GameHolder();
    void remove(int GameId);
    void add(GameInstance * Game);
    std::vector<GameInstance *> getGames();
    GameInstance* get(int GameId);
};


#endif //DICESSERVER_GAMEHOLDER_H
