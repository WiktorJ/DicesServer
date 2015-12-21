//
// Created by wiktor on 20.12.15.
//

#ifndef DICESSERVER_CLIENTSERVER_H
#define DICESSERVER_CLIENTSERVER_H
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "../../Logger/LogParser.h"
#include <pthread.h>

using namespace std;

class ConnectionServer {

public:
    bool init(int port);
    void run();
    void stop();

    bool sendClose(string id);
    bool sendData(string id, string data);

    ConnectionServer();

private:
    LogParser Logger;
    bool getWebsocket(const string &id, websocketpp::connection_hdl &hdl);

    websocketpp::server<websocketpp::config::asio> server;
    map<string, websocketpp::connection_hdl> websockets;
    pthread_rwlock_t websocketsLock;

    // callbacks
    bool on_validate(websocketpp::connection_hdl hdl);
    void on_fail(websocketpp::connection_hdl hdl);
    void on_close(websocketpp::connection_hdl hdl);
    void on_message(websocketpp::connection_hdl hdl);
};


#endif //DICESSERVER_CLIENTSERVER_H
