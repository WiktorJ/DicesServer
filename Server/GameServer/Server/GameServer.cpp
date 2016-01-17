//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameServer.h"
#include "Serializer/GamesSerializer.h"
#include "Serializer/CmdDeseriallizer.h"
#include "../Instance/Client/GameResponseSerializer.h"

WaitingRoom &GameServer::getWaitingRoom() {
    return WaitingRoom_;
}

boost::property_tree::ptree GameServer::getActiveGames() {


    boost::property_tree::ptree activeGames = GamesSerializer::serialize(Games.getGames(), Env);

    return activeGames;
}

void GameServer::run() {

    Env = JNIInstance::getInstance().attacheThread();
    Factory.setEnv(Env);

    while(true){
        readRequests();

        boost::this_thread::interruption_point();
    }
}

void GameServer::readRequests() {
    std::vector<ClientMovement> Requests = WaitingRoom_.getRequests();

    for(std::vector<ClientMovement>::iterator iterator = Requests.begin(); iterator != Requests.end(); iterator++){
        boost::property_tree::ptree move = (*iterator).getMove();

        std::string command;

        try {
            command = CmdDeseriallizer::readCommand(move);
        } catch(const boost::property_tree::ptree_error &exception){
            Logger.log("Client : " + (*iterator).getUsername() + " - invalid json");
            continue;
        }
        if(command == "disconnect"){
            Client* client = WaitingRoom_.removeClient((*iterator).getUsername());
            if(client != NULL){
                delete client;
                Logger.log("Client : " + (*iterator).getUsername() + " - disconnected");
            }


        } else if(command == "join"){

            GameInstance* game = Games.get(CmdDeseriallizer::getGameID(move));

            if(game == NULL){
                Logger.log("Client : " + (*iterator).getUsername() + " - tried to join unexisting game");

                WaitingRoom_.sendDataToClient((*iterator).getUsername(), (GameResponseSerializer::serializeResponse(command, status::FAILURE, boost::property_tree::ptree("COULD NOT FIND REQUESTED GAME"))));
                return;
            }

            Client* client = WaitingRoom_.removeClient((*iterator).getUsername());
            client->setPlayer();

            game->getClientGroup().addSubscriber(client);
            client->addRequest(move);

            Logger.log("Client : " + (*iterator).getUsername() + " - joined a game : " + std::to_string(game->getId()));

        } else if(command == "observe"){
            GameInstance* game = Games.get(CmdDeseriallizer::getGameID(move));

            if(game == NULL){
                Logger.log("Client : " + (*iterator).getUsername() + " - tried to observer unexisting game");

                WaitingRoom_.sendDataToClient((*iterator).getUsername(), (GameResponseSerializer::serializeResponse(command, status::FAILURE, boost::property_tree::ptree("COULD NOT FIND REQUESTED GAME"))));
                continue;
            }

            Client* client = WaitingRoom_.removeClient((*iterator).getUsername());
            client->setObserver();

            game->getClientGroup().addSubscriber(client);
            client->addRequest(move);

            Logger.log("Client : " + (*iterator).getUsername() + " - observing a game : " + std::to_string(game->getId()));

        } else if(command == "create") {
            GameInstance* game = Factory.createGame(move.get_child("data"), WaitingRoom_);

            if(game == NULL){
                Logger.log("Client : " + (*iterator).getUsername() + " - failed to create a game ");

                WaitingRoom_.sendDataToClient((*iterator).getUsername(), (GameResponseSerializer::serializeResponse(command, status::FAILURE, boost::property_tree::ptree("COULD NOT CREATE GAME"))));

                continue;
            }

            Games.add(game);

            WaitingRoom_.sendDataToClient((*iterator).getUsername(), (GameResponseSerializer::serializeResponse(command, status::SUCCESS, boost::property_tree::ptree(std::to_string(game->getId())))));

            Logger.log("Client : " + (*iterator).getUsername() + " - created a game: " + std::to_string(game->getId()));
        } else if(command == "activeGames"){
            WaitingRoom_.sendDataToClient((*iterator).getUsername(), GameResponseSerializer::serializeResponse(command, status::SUCCESS, getActiveGames()));

            Logger.log("Client : " + (*iterator).getUsername() + " - asked for active games");
        } else {
            Logger.log("Client : " + (*iterator).getUsername() + " - invalid command: " + command);

            WaitingRoom_.sendDataToClient((*iterator).getUsername(), GameResponseSerializer::serializeResponse(command, status::FAILURE, boost::property_tree::ptree("WRONG COMMAND")));
        }
    }
}

void GameServer::start() {
    Thread = boost::thread(boost::bind(&GameServer::run, this));

    Logger.log("Starting");
}

void GameServer::stop() {
    Logger.log("Stopping");

    Thread.interrupt();

    Thread.join();

    Logger.log("Stopped");
}

GameServer::GameServer() : Logger("GameServer"){

}

boost::property_tree::ptree GameServer::getActiveGamesLocally() {
    boost::property_tree::ptree activeGames = GamesSerializer::serialize(Games.getGames(), JNIInstance::getInstance().getCurr());

    return activeGames;
}
