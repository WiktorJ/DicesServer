//
// Created by Wojciech Grabis on 13.12.15.
//

#include "GameReader.h"
#include "GameCmdDeseriallizer.h"

GameReader::GameReader(ClientGroup &Clients, GameController* Controller) : Clients(Clients), Controller(Controller){

}

void GameReader::readMovement() {
    std::vector<ClientMovement> requests = Clients.getRequests();
    for(std::vector<ClientMovement>::iterator it = requests.begin(); it != requests.end(); it++){
        boost::property_tree::ptree data = (*it).getMove();

        std::string command;
        try {
            command = GameCmdDeseriallizer::readCommand(data);
        } catch(const boost::property_tree::ptree_error &exception){
            std::cout << "GameReader: Invalid json" << std::endl;
            //TODO LOGGER
            break;
        }

        if(command == "quit"){
            Clients.removeSubscriber((*it).getUsername());
            if((*it).isPlayer()) Controller->removePlayer((*it).getUsername());

        } else if(command == "disconnect"){
            Clients.removeClient((*it).getUsername());
            if((*it).isPlayer()) Controller->removePlayer((*it).getUsername());

        } else if(command == "join"){
            Controller->addPlayer((*it).getUsername());

        } else if(command == "observe") {
            //do nothing
        } else if(command == "move"){
            if((*it).isPlayer())Controller->makeMove(data);
            else true;//TODO THROW EXCEPTION
        } else{
            //TODO THROW EXCEPTION
        }

    }
}

void GameReader::start() {
    thread = boost::thread(boost::bind(&GameReader::run, this));

}

void GameReader::stop() {
    thread.interrupt();

    thread.join();
}


void GameReader::run() {
    while(1){
        readMovement();

        boost::this_thread::interruption_point();
    }
}
