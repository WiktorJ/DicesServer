//
// Created by Wojciech Grabis on 13.12.15.
//

#include "Client.h"

//TODO

std::string Client::getUsername() {
    return Username;
}

void Client::addRequest(boost::property_tree::ptree Request){
    //TODO
    ClientMovement move(Username, Player, Request);

    Requests->addRequest(move);
}

void Client::sendData(std::string data) {

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

Client::Client(std::string Username, ClientConnector clientConnector) : Username(Username), clientConnector(clientConnector){

}

void Client::subscribe(RequestQueue *Requests) {
    this->Requests = Requests;
}
