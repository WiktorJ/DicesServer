//
// Created by wiktor on 21.12.15.
//

#ifndef DICESSERVER_CLIENTCONNECTOR_H
#define DICESSERVER_CLIENTCONNECTOR_H


class ClientConnector {

private:
    ConnectionServer socket;
    ClientConnector(ConnectionServer socket);
public:
    send();
    receive();
};


#endif //DICESSERVER_CLIENTCONNECTOR_H
