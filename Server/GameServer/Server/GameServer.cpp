//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameServer.h"
#include "Serializer/GamesSerializer.h"
#include "Serializer/CmdDeseriallizer.h"

WaitingRoom &GameServer::getWaitingRoom() {
    return WaitingRoom_;
}

boost::property_tree::ptree GameServer::getActiveGames() {


    boost::property_tree::ptree activeGames = GamesSerializer::serialize(Games.getGames());

    return activeGames;
}

void GameServer::run() {


    while(true){
        readRequests();

        boost::this_thread::interruption_point();
    }
}

void GameServer::readRequests() {
    std::vector<ClientMovement> Requests = WaitingRoom_.getRequests();

    for(std::vector<ClientMovement>::iterator iterator = Requests.begin(); iterator != Requests.end(); iterator++){
        int gameId;
        boost::property_tree::ptree move = (*iterator).getMove();

        std::string command;

        try {
            command = CmdDeseriallizer::readCommand(move, &gameId);
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
            GameInstance* game = Games.get(gameId);

            if(game == NULL){

                //TODO THROW EXCEPTION
                return;
            }

            Client* client = WaitingRoom_.removeClient((*iterator).getUsername());
            client->setPlayer();

            game->getClientGroup().addSubscriber(client);
            client->addRequest(move);

            //TODO
            Logger.log("Client : " + (*iterator).getUsername() + " - joined a game : " + std::to_string(game->getId()));

        } else if(command == "observe"){
            GameInstance* game = Games.get(gameId);

            if(game == NULL){
                //TODO THROW EXCEPTION
                return;
            }

            Client* client = WaitingRoom_.removeClient((*iterator).getUsername());
            client->setObserver();

            game->getClientGroup().addSubscriber(client);
            client->addRequest(move);

            Logger.log("Client : " + (*iterator).getUsername() + " - observing a game : " + std::to_string(game->getId()));

        } else if(command == "create") {
            GameInstance* game = Factory.createGame(move, WaitingRoom_);

            Games.add(game);

            Logger.log("Client : " + (*iterator).getUsername() + " - created a game: " + std::to_string(game->getId()));
        } else {
            Logger.log("Client : " + (*iterator).getUsername() + " - invalid command: " + command);

            //TODO THROW EXCEPION
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
