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
    boost::unique_lock<boost::mutex> lock(Mutex);

    update();

    for(std::vector<GameInstance *>::iterator iterator = Games.begin(); iterator != Games.end(); iterator++)
        if((*iterator)->getId() == GameId){
            delete (*iterator);
            Games.erase(iterator);

            return;
        }
}

void GameHolder::add(GameInstance *Game) {
    boost::unique_lock<boost::mutex> lock(Mutex);

    update();

    Games.push_back(Game);
    Game->start();

}

GameInstance *GameHolder::get(int GameId) {
    boost::unique_lock<boost::mutex> lock(Mutex);

    update();

    for(std::vector<GameInstance *>::iterator iterator = Games.begin(); iterator != Games.end(); iterator++)
        if((*iterator)->getId() == GameId){

            return (*iterator);
        }

    return NULL;
}

GameHolder::GameHolder() {

}

std::vector<GameInstance *> GameHolder::getGames() {
    boost::unique_lock<boost::mutex> lock(Mutex);

    update();

    std::vector<GameInstance *> result = Games;

    return result;
}
