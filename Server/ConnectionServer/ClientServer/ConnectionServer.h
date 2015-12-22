//
// Created by wiktor on 20.12.15.
//

#ifndef DICESSERVER_CONNECTIONSERVER_H
#define DICESSERVER_CONNECTIONSERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "../../Logger/LogParser.h"
#include "ClientServer.h"
#include <pthread.h>

class ClientServer;
class WaitingRoom;

using namespace std;

class ConnectionServer {

public:
    bool init(int port);

    void run();

    void stop();

    bool sendClose(string id);

    bool sendData(string data, string id);

    ConnectionServer(WaitingRoom* waitingRoom);

private:
    LogParser Logger;
    ClientServer* clientServer;

    bool getWebsocket(const string &id, websocketpp::connection_hdl &hdl);

    websocketpp::server<websocketpp::config::asio> server;
    map<string, websocketpp::connection_hdl> websockets;
    pthread_rwlock_t websocketsLock;

    // callbacks
    bool on_validate(websocketpp::connection_hdl hdl);

    void on_fail(websocketpp::connection_hdl hdl);

    void on_close(websocketpp::connection_hdl hdl);

    void on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg);
};


#endif //DICESSERVER_CONNECTIONSERVER_H
