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
        } catch(const boost::property_tree::ptree &exception){
            std::cout << "GameServer: Invalid json" << std::endl;
            //TODO LOGGER
            continue;
        }
        if(command == "disconnect"){

        } else if(command == "join"){
            GameInstance* game = Games.get(gameId);

            if(game == NULL){

                //TODO THROW EXCEPTION
                return;
            }

            Client* client = WaitingRoom_.removeClient((*iterator).getUsername());
            client->setPlayer();
            client->addRequest(move);

            game->getClientGroup().addSubscriber(client);

            //TODO
            std::cout << "Joined:" << client->getUsername() << std::endl;

        } else if(command == "observe"){
            GameInstance* game = Games.get(gameId);

            if(game == NULL){
                //TODO THROW EXCEPTION
                return;
            }

            Client* client = WaitingRoom_.removeClient((*iterator).getUsername());
            client->setObserver();
            client->addRequest(move);

            game->getClientGroup().addSubscriber(client);

            std::cout << "Observing:" << client->getUsername() << std::endl;

        } else if(command == "create") {
            Games.add(Factory.createGame(move, WaitingRoom_));

            std::cout << "Creating game" << std::endl;
        } else {
            std::cout << "Command not found" << std::endl;

            //TODO THROW EXCEPION
        }
    }
}

void GameServer::start() {
    Thread = boost::thread(boost::bind(&GameServer::run, this));
}

void GameServer::stop() {
    Thread.interrupt();

    Thread.join();
}
