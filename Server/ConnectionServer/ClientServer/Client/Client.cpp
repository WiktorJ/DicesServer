//
// Created by Wojciech Grabis on 13.12.15.
//

#include "Client.h"
#include "Serializer/ClientSerializer.h"

//TODO

std::string Client::getUsername() {
    return Username;
}

void Client::addRequest(boost::property_tree::ptree Request) {
    //TODO
    ClientMovement move(Username, Player, Request);

    Requests->addRequest(move);
}

void Client::sendData(boost::property_tree::ptree data, std::string command) {
    stringstream ss;
    data.put_child("command", boost::property_tree::ptree(command));
    boost::property_tree::write_json(ss, ClientSerializer::serialize(Username, data, command));

    sender->send(ss.str());
}

void Client::setPlayer() {
    Player = true;
}

void Client::setObserver() {
    Player = false;
}

bool Client::isPlayer() {
    return Player;
}

//Client::Client(std::string Username, ClientConnector clientConnector)
Client::Client(std::string Username, Sender* sender)
        : Username(Username){
    this->sender = sender;
}

void Client::subscribe(RequestQueue *Requests) {
    this->Requests = Requests;
}
