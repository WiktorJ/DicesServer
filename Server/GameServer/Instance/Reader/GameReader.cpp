//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameReader.h"
#include "GameCmdDeseriallizer.h"
#include "../../Java/Exception/JNIException.h"

GameReader::GameReader(ClientGroup &Clients, GameController* Controller) : Clients(Clients), Controller(Controller), Logger("GameReader"){

}

void GameReader::readMovement() {
    std::vector<ClientMovement> requests = Clients.getRequests();
    for(std::vector<ClientMovement>::iterator it = requests.begin(); it != requests.end(); it++){
        boost::property_tree::ptree data = (*it).getMove();

        std::string command;
        try {
            command = GameCmdDeseriallizer::readCommand(data);
        } catch(const boost::property_tree::ptree_error &exception){
            Logger.log("Client : " + (*it).getUsername() + " - invalid json");

            continue;
        }

        if(command == "quit"){
            Clients.removeSubscriber((*it).getUsername());
            if((*it).isPlayer()) Controller->removePlayer((*it).getUsername());

            Logger.log("Client : " + (*it).getUsername() + " - player quit the game");

        } else if(command == "disconnect"){
            Clients.removeClient((*it).getUsername());
            if((*it).isPlayer()) Controller->removePlayer((*it).getUsername());

            Logger.log("Client : " + (*it).getUsername() + " - player disconnected");

        } else if(command == "join"){
            Controller->addPlayer((*it).getUsername());

            Logger.log("Client : " + (*it).getUsername() + " - player joined");

        } else if(command == "observe") {
            Logger.log("Client : " + (*it).getUsername() + " - client observing the game");
            //do nothing
        } else if(command == "move"){
            if((*it).isPlayer())Controller->makeMove(data);
            else true;//TODO THROW EXCEPTION

            Logger.log("Client : " + (*it).getUsername() + " - client requested move");
        } else{
            Logger.log("Client : " + (*it).getUsername() + " - bad command :" + command);
        }

    }
}

void GameReader::start() {
    Logger.log("starting");

    thread = boost::thread(boost::bind(&GameReader::run, this));

}

void GameReader::stop() {
    thread.interrupt();
    Logger.log("stopping");

    thread.join();
    Logger.log("stopped");
}


void GameReader::run() {
    //TODO WILL FUCK UP EVERYTHING

    Controller->bind();

    while(1){
        readMovement();

        boost::this_thread::interruption_point();
    }
}
