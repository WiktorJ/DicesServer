//
// Created by wiktor on 21.12.15.
//

#include "ClientServer.h"
#include "Exception/ClientNotFoundException.h"
#include "Exception/ConnectorNotFoundException.h"
#include "Exception/NameTakenException.h"

using namespace std;

void ClientServer::addClient(string name, string clientAddress, Sender* sender) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    map<string, std::vector<Client *>>::iterator iter =  clients.find(clientAddress);

    if(iter == clients.end()) throw ConnectorNotFoundException();

    if(ClientNames.find(name) != ClientNames.end())throw NameTakenException();


    Client *client = new Client(name, sender);

    ClientNames.insert(name);
    iter->second.push_back(client);
    waitingRoom->addClient(client);
}

Client* ClientServer::getClient(std::string clientAddress, string name) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    if ( clients.find(clientAddress) == clients.end()) {
        throw ConnectorNotFoundException();
    } else {
        map<string, std::vector<Client *>>::iterator iter =  clients.find(clientAddress);

        for(std::vector<Client *>::iterator it= iter->second.begin(); it != iter->second.end(); iter++){
            if((*it)->getUsername() == name){
                return (*it);
            }
        }

        throw ClientNotFoundException();
    }
}

void ClientServer::removeClient(std::string clientAddress, string name) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    if ( clients.find(clientAddress) == clients.end()) {
        throw ConnectorNotFoundException();
    } else {
        map<string, std::vector<Client *>>::iterator iter =  clients.find(clientAddress);

        for(std::vector<Client *>::iterator it= iter->second.begin(); it != iter->second.end(); iter++){
            if((*it)->getUsername() == name){
                iter->second.erase(it);
                ClientNames.erase(ClientNames.find(name));
            }
        }

        throw ClientNotFoundException();
    }
}

void ClientServer::addClientEndpoint(string clientAddress) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    std::vector<Client *> vec;
    clients.insert(pair<string,  std::vector<Client *>>(clientAddress, vec));
}


ClientServer::ClientServer(WaitingRoom* waitingRoom) : Logger("ClientServer"){
    this->waitingRoom = waitingRoom;
}

void ClientServer::removeClientEndpoint(std::string clientAddress) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    if ( clients.find(clientAddress) == clients.end()) {
        throw ConnectorNotFoundException();
    } else {
        map<string, std::vector<Client *>>::iterator iter =  clients.find(clientAddress);
        clients.erase(iter);
    }
}

std::vector<Client *> ClientServer::getClientList(std::string clientAddress) {
    boost::unique_lock<boost::mutex> lock(*Mutex);

    if ( clients.find(clientAddress) == clients.end()) {
        throw ConnectorNotFoundException();
    } else {
        map<string, std::vector<Client *>>::iterator iter =  clients.find(clientAddress);
        return (*iter).second;
    }
}
