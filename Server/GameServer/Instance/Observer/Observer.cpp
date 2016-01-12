//
// Created by Wojciech Grabis on 13.12.15.
//

#include "Observer.h"
#include "ObsCmdDeserializer.h"

using namespace std;

Observer::Observer(ClientGroup& Clients, JObserver Observer_) : Clients(Clients), Observer_(Observer_), Logger("Observer"){

}

void Observer::listen() {
    Observer_.attach(JNIInstance::getInstance().attacheThread());

    while(1){
        std::string data = Observer_.notify();

        if(Observer_.isFinished()){
            Clients.clear();
            break;
        }

        boost::property_tree::ptree json;
        std::stringstream ss(data);
        try {
            boost::property_tree::read_json(ss, json);
        } catch(const boost::property_tree::json_parser_error &e){
            Logger.log("Could not parse json" + ss.str());
        }
        std::string command = ObsCmdDeserializer::deserialize(json);

        if(command == "removePlayer"){
            std::string username = ObsCmdDeserializer::deserializeNick(json);

            Clients.sendDataToPlayer(username, boost::property_tree::ptree("Empty"), "remove");

            Clients.removeClient(username);
        } else if(command == "gameEnded"){
            Clients.clear();
            break;
        } else if(command == "stateUpdated"){
            Clients.sendData(json, "gameState");
        } else {
            true;
        }

        boost::this_thread::interruption_point();
    }
}
