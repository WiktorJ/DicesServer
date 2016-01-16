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
    ClientMovement move(Username, Player, Request);

    Requests->addRequest(move);
}

void Client::sendData(boost::property_tree::ptree data) {
    sender->send(data);
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

Client::Client(std::string Username, Sender* sender)
        : Username(Username){
    this->sender = sender;
}

void Client::subscribe(RequestQueue *Requests) {
    this->Requests = Requests;
}

Client::~Client() {
    delete sender;
}
