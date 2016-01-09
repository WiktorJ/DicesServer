//
// Created by wiktor on 21.12.15.
//

#include "ClientServer.h"
#include "../Connector/Network/Sender.h"

using namespace std;

void ClientServer::addClient(string name, string clientAddress, Sender* sender) {
    Client *client = new Client(name, sender);
    map<string, std::vector<Client *>>::iterator iter =  clients.find(clientAddress);
    iter->second.push_back(client);
    waitingRoom->addClient(client);
}

Client* ClientServer::getClient(std::string clientAddress, string name) {
    if ( clients.find(clientAddress) == clients.end()) {
            cout<<"Some error message";
        throw "get Client exception";
    } else {
        map<string, std::vector<Client *>>::iterator iter =  clients.find(clientAddress);
//        clients.erase(iter);

        for(std::vector<Client *>::iterator it= iter->second.begin(); it != iter->second.end(); iter++){
            if((*it)->getUsername() == name){
                return (*it);
            }
        }
    }
}

bool ClientServer::removeClient(std::string clientAddress, string name) {
    if ( clients.find(clientAddress) == clients.end()) {
        cout << "Some error message";
        return false;
    } else {
        map<string, std::vector<Client *>>::iterator iter =  clients.find(clientAddress);
//        clients.erase(iter);

        for(std::vector<Client *>::iterator it= iter->second.begin(); it != iter->second.end(); iter++){
            if((*it)->getUsername() == name){
                iter->second.erase(it);
                return true;
            }
        }
    }
    return false;
}

void ClientServer::addClientEndpoint(string clientAddress) {
    std::vector<Client *> vec;
    clients.insert(pair<string,  std::vector<Client *>>(clientAddress, vec));
}


ClientServer::ClientServer(WaitingRoom* waitingRoom) {
    this->waitingRoom = waitingRoom;
}

void ClientServer::removeClientEndpoint(std::string clientAddress) {
    if ( clients.find(clientAddress) == clients.end()) {
        cout << "Some error message";
    } else {
        map<string, std::vector<Client *>>::iterator iter =  clients.find(clientAddress);
        clients.erase(iter);
    }
}
