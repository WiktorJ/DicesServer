//
// Created by Wojciech Grabis on 08.12.15.
//

#include "Sender.h"

void Sender::send(std::string data) {
    socket->sendData(data, socketId);
}

void Sender::receive() {

}


Sender::Sender(ConnectionServer* server, std::string socketId) : socketId(socketId){
    socket = server;
}
