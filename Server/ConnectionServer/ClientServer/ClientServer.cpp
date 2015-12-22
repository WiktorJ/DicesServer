//
// Created by wiktor on 21.12.15.
//

#include "ClientServer.h"
#include "../Connector/Network/Sender.h"

using namespace std;

void ClientServer::addClient(string name, string clientAddress, Sender* sender) {
    Client *client = new Client(name, sender);
    map<string, std::vector<Client>>::iterator iter =  clients.find(clientAddress);
    iter->second.push_back(*client);
    waitingRoom->addClient(client);
}

Client ClientServer::getClient(string name) {
    if ( clients.find(name) == clients.end()) {
            cout<<"Some error message";
        throw "get Client exception";
    } else {
        map<string, std::vector<Client>>::iterator iter =  clients.find(name);
        return  iter->second.front();//TODO: iterate
    }
}

bool ClientServer::removeClient(string name) {
    if ( clients.find(name) == clients.end()) {
        cout << "Some error message";
        return false;
    } else {
        map<string, std::vector<Client>>::iterator iter =  clients.find(name);
        clients.erase(iter);
    }
    waitingRoom->removeClient(name);
}

void ClientServer::addClientEndpoint(string clientAddress) {
    std::vector<Client> vec;
    clients.insert(pair<string,  std::vector<Client>>(clientAddress, vec));
}


ClientServer::ClientServer(WaitingRoom* waitingRoom) {
    this->waitingRoom = waitingRoom;
}