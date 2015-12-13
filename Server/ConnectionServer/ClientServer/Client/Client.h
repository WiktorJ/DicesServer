//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_CLIENT_H
#define DICESSERVER_CLIENT_H

#include <string>

class Client {
private:
    //Sender
    std::string Username;
    std::string Request; // to json
    bool Blocked;
    bool Free;
    bool Player;
public:
    std::string getUsername();
    void addRequest(std::string Request);
    void sendData(std::string data);
    std::string getRequest();
    void setObserver();
    void setPlayer();
    bool isPlayer();
};


#endif //DICESSERVER_CLIENT_H
