//
// Created by wiktor on 21.12.15.
//

#ifndef DICESSERVER_CLIENTSERVER_H
#define DICESSERVER_CLIENTSERVER_H

using namespace std;

class ClientServer {
private:
    map <string, vector<Client>> clients;
    WaitingRoom waitingRoom;

public:
    void addClient(ClientConnector clientConnector, string name);
    void removeClient(string name);
    Client getClient(string name);

};


#endif //DICESSERVER_CLIENTSERVER_H
