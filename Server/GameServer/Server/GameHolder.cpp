//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameHolder.h"

GameHolder::~GameHolder() {
    std::vector<GameInstance *>::iterator iterator = Games.begin();

    while(iterator != Games.end()){
        delete (*iterator);
        iterator = Games.erase(iterator);
    }
}

void GameHolder::update(){

    for(std::vector<GameInstance *>::iterator iterator = Games.begin(); iterator != Games.end();)
        if((*iterator)->ended()){
            delete (*iterator);
            iterator = Games.erase(iterator);
        } else { iterator++;}


}

void GameHolder::remove(int GameId) {
    Mutex.lock();

    update();

    for(std::vector<GameInstance *>::iterator iterator = Games.begin(); iterator != Games.end(); iterator++)
        if((*iterator)->getId() == GameId){
            delete (*iterator);
            Games.erase(iterator);

            Mutex.unlock();
            return;
        }

    Mutex.unlock();
}

void GameHolder::add(GameInstance *Game) {
    Mutex.lock();

    update();

    Games.push_back(Game);

    Mutex.unlock();
}

GameInstance *GameHolder::get(int GameId) {
    Mutex.lock();

    update();

    for(std::vector<GameInstance *>::iterator iterator = Games.begin(); iterator != Games.end(); iterator++)
        if((*iterator)->getId() == GameId){

            Mutex.unlock();
            return (*iterator);
        }

    Mutex.unlock();
    return NULL;
}

GameHolder::GameHolder() {

}

std::vector<GameInstance *> GameHolder::getGames() {
    Mutex.lock();

    update();

    std::vector<GameInstance *> result = Games;

    Mutex.unlock();
    return result;
}
