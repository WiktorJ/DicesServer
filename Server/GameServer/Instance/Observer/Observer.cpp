//
// Created by Wojciech Grabis on 13.12.15.
//

#include "Observer.h"
#include "ObsCmdDeserializer.h"
#include "../Client/GameResponseSerializer.h"

using namespace std;

Observer::Observer(ClientGroup& Clients, JObserver Observer_) : Clients(Clients), Observer_(Observer_), Logger("Observer"){

}

void Observer::listen() {
    Observer_.attach(JNIInstance::getInstance().attacheThread());

    while(1){
        std::string data = Observer_.notify();


        boost::property_tree::ptree json;
        std::stringstream ss(data);

        try {
            boost::property_tree::read_json(ss, json);
            std::string command;

            try {
                 command = ObsCmdDeserializer::deserialize(json);
            } catch (const boost::property_tree::ptree_error &exception){
                Logger.log("Could not get the json deserialization for observer" + ss.str());

                command = "";
            }
            if(command == "removePlayer"){
                std::string username;
                try {
                     username = ObsCmdDeserializer::deserializeNick(json);

                     Clients.sendDataToPlayer(username, GameResponseSerializer::serializeResponse(command, status::SUCCESS, boost::property_tree::ptree("CONTROLLER ASKED FOR REMOVAL")));

                     Clients.removeClient(username);
                } catch (const boost::property_tree::ptree_error &exception){
                    Logger.log("Could not get nickname for removal");


                }
            } else if(command == "stateUpdated"){
                Clients.sendData(GameResponseSerializer::serializeResponse(command, status::SUCCESS, json));
            } else {
                Logger.log("Got an invalid command" + command);
            }

        } catch(const boost::property_tree::json_parser_error &e){
            Logger.log("Could not parse JSON");

        }

        if(Observer_.isFinished()){
            Clients.sendData(GameResponseSerializer::serializeResponse("gameEnded", status::SUCCESS, boost::property_tree::ptree("GAME STATE CHANGED TO FINISH")));

            Clients.clear();
            break;
        }

        boost::this_thread::interruption_point();
    }
}
