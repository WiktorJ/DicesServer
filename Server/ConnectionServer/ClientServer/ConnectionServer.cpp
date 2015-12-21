//
// Created by wiktor on 20.12.15.
//

#include "ConnectionServer.h"
using namespace std;



ConnectionServer::ConnectionServer() : Logger("ConnectionServer") {
    websocketsLock = PTHREAD_RWLOCK_INITIALIZER;
}

bool ConnectionServer::init(int port) {
    server.init_asio();
    server.set_open_handler(websocketpp::lib::bind(&ConnectionServer::on_validate, this, websocketpp::lib::placeholders::_1));
    server.set_fail_handler(websocketpp::lib::bind(&ConnectionServer::on_fail, this,  websocketpp::lib::placeholders::_1));
    server.set_close_handler(websocketpp::lib::bind(&ConnectionServer::on_close, this, websocketpp::lib::placeholders::_1));
    server.set_message_handler(websocketpp::lib::bind(&ConnectionServer::on_message, this, websocketpp::lib::placeholders::_2));
    try {
        server.listen(port);
    } catch (websocketpp::exception const &e) {
        Logger.log("error in ConnectionServer:init(1)");
        Logger.log(e.what());
    }

    websocketpp::lib::error_code ec;
    server.start_accept(ec);
    if (ec) {
        Logger.log("error in ConnectionServer:init(1)");
        Logger.log(ec.message());
        return false;
    }

    return true;
}

void ConnectionServer::run() {
    try {
        server.run();
    } catch (websocketpp::exception const &e) {
        Logger.log("exception in ConnectionServer::run()");
        Logger.log(e.what());
    }
}

void ConnectionServer::stop() {
    // Stopping the Websocket listener and closing outstanding connections.
    websocketpp::lib::error_code ec;
    server.stop_listening(ec);
    if (ec) {
        Logger.log("error in ConnectionServer:stop()");
        Logger.log(ec.message());
        return;
    }

    map<string, websocketpp::connection_hdl>::iterator it;
    for (it = websockets.begin(); it != websockets.end(); ++it) {
        websocketpp::lib::error_code ec;
        string data = "reson";
        server.close(it->second, websocketpp::close::status::normal, data, ec); // send text message.
        if (ec) {
            Logger.log("error in ConnectionServer:stop()");
            Logger.log(ec.message());
        }
    }

    // Stop the endpoint.
    server.stop();
}

bool ConnectionServer::on_validate(websocketpp::connection_hdl hdl) {
    websocketpp::server<websocketpp::config::asio>::connection_ptr con = server.get_con_from_hdl(hdl);
    websocketpp::uri_ptr uri = con->get_uri();
    string query = uri->get_query(); // returns empty string if no query string set.
//    if (!query.empty()) {
//        //get id from query
//    }
//    else {
//        // Reject if no query parameter provided, for example.
//        return false;
//    }

//    if (pthread_rwlock_wrlock(&websocketsLock) != 0) {
//        Logger.log("Failed to write-lock websocketsLock.");
//    }


    string id = "id";

    websockets.insert(std::pair<string, websocketpp::connection_hdl>(id, hdl));
//    if (pthread_rwlock_unlock(&websocketsLock) != 0) {
//        Logger.log("Failed to unlock websocketsLock.");
//    }

    return true;
}

void ConnectionServer::on_fail(websocketpp::connection_hdl hdl) {
    websocketpp::server<websocketpp::config::asio>::connection_ptr con = server.get_con_from_hdl(hdl);
    websocketpp::lib::error_code ec = con->get_ec();
    Logger.log("ConnectionServer:on_fail(1)");
    Logger.log(ec.message());
}

void ConnectionServer::on_close(websocketpp::connection_hdl hdl) {
    // Websocket connection closed.
}


void ConnectionServer::on_message(websocketpp::connection_hdl hdl) {
    Logger.log("RECEIVED MESSAGE");
}

bool ConnectionServer::sendData(string id, string data) {
    websocketpp:: connection_hdl hdl;
    if (!getWebsocket(id, hdl)) {
        Logger.log("There is no socket with id: " + id);
        return false;
    }

    websocketpp::lib::error_code ec;
    server.send(hdl, data, websocketpp::frame::opcode::text, ec); // send text message.
    if (ec) {
        Logger.log("error in ConnectionServer:sendData(2)");
        Logger.log(ec.message());
        return false;
    }

    return true;
}

bool ConnectionServer::getWebsocket(const string &id, websocketpp::connection_hdl &hdl) {
//    if (pthread_rwlock_wrlock(&websocketsLock) != 0) {
//        Logger.log("Failed to write-lock websocketsLock.");
//    }

    map<string, websocketpp::connection_hdl>::iterator iter = websockets.find(id);
    if (iter == websockets.end()) {
        return false;
    }

    hdl = iter->second;
//    if (pthread_rwlock_unlock(&websocketsLock) != 0) {
//        Logger.log("Failed to unlock websocketsLock.");
//    }

    return true;
}



