//
// Created by Wojciech Grabis on 13.12.15.
//

#include "Client.h"

//TODO

std::string Client::getUsername() {
    return "";
}

void Client::addRequest(boost::property_tree::ptree Request){
    //TODO

    this->Request = Request;
}

void Client::sendData(std::string data) {

}

boost::property_tree::ptree Client::getRequest() {
    return this->Request;
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
