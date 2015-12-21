//
// Created by wiktor on 21.12.15.
//

#include "ClientServer.h"
#include "Client/Client.h"

void ClientServer::addClient(ClientConnector clientConnector) {
    Client client (name, cientConnector);
    if ( clients.find(name) == clients.end()) {
        std::vector<Client> vec;
        vec.push_back(client);
        clients.insert(pair<string, Client>(name, vec));
    } else {
        map<string, std::vector<Client>>::iterator iter =  clients.find(name);
        iter->second.push_back(client);
    }
    waitingRoom.addClient(&client);
}

Client ClientServer::getClient(::ClientServer::string name) {
    if ( clients.find(name) == clients.end()) {
            cout<<"Some error message";
        return nullptr;
    } else {
        map<string, std::vector<Client>>::iterator iter =  clients.find(name);
        return  iter->second;
    }
}

bool ClientServer::removeClient(::ClientServer::string name) {
    if ( clients.find(name) == clients.end()) {
        cout << "Some error message";
        return false;
    } else {
        map<string, std::vector<Client>>::iterator iter =  clients.erase(name);
        clients.erase(iter);
    }
    waitingRoom.removeClient(name);
}

