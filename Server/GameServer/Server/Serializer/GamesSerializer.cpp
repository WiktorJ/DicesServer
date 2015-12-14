//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GamesSerializer.h"

boost::property_tree::ptree GamesSerializer::serialize(std::vector<GameInstance *> games) {

    boost::property_tree::ptree result;
    result.put_child("type", boost::property_tree::ptree("GameList"));

    for(std::vector<GameInstance *>::iterator it = games.begin(); it != games.end(); it++){

        boost::property_tree::ptree game;

        game.put_child("gameId", boost::property_tree::ptree(std::to_string((*it)->getId())));
        game.put_child("gameInfo", (*it)->getInfo());

        result.push_back(std::make_pair("", game));
    }

    result.add_child("activeGames", result);
    return result;
}
