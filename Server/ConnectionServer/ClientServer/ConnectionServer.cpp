//
// Created by wiktor on 20.12.15.
//

#include "ConnectionServer.h"
#include "../Connector/Network/Sender.h"

using namespace std;



ConnectionServer::ConnectionServer(WaitingRoom *waitingRoom) : Logger("ConnectionServer") {
    clientServer = new ClientServer(waitingRoom);
}

bool ConnectionServer::init(int port) {
    server.init_asio();
    server.set_open_handler(websocketpp::lib::bind(&ConnectionServer::on_validate, this, websocketpp::lib::placeholders::_1));
    server.set_fail_handler(websocketpp::lib::bind(&ConnectionServer::on_fail, this,  websocketpp::lib::placeholders::_1));
    server.set_close_handler(websocketpp::lib::bind(&ConnectionServer::on_close, this, websocketpp::lib::placeholders::_1));
    server.set_message_handler(websocketpp::lib::bind(&ConnectionServer::on_message, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
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
    Logger.log("Trying to stop the server");
    // Stop the endpoint.
    server.stop();
    Logger.log("Server stopped");
}

bool ConnectionServer::on_validate(websocketpp::connection_hdl hdl) {
    websocketpp::server<websocketpp::config::asio>::connection_ptr con = server.get_con_from_hdl(hdl);
    websocketpp::uri_ptr uri = con->get_uri();
    string id;
    string query = uri->get_query(); // returns empty string if no query string set.
    if (!query.empty()) {
        id = query;
    }
    else {
        // Reject if no query parameter provided, for example.
        return false;
    }

//    }




    websockets.insert(std::pair<string, websocketpp::connection_hdl>(id, hdl));
    clientServer->addClientEndpoint(id);

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


void ConnectionServer::on_message(websocketpp::connection_hdl hdl,  websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
    //Logger.log(msg->get_payload());
    //deserialize message and get clientAddress and nickname
    boost::property_tree::ptree parsed;

    std::stringstream ss(msg->get_payload());
    try {
        boost::property_tree::read_json(ss, parsed);
    } catch(const boost::property_tree::json_parser_error &exception){
        Logger.log("Invalid json received : " + std::string(msg->get_payload()));
        return;
    }

    string clientAddress;
    string nickname = "INVALID_NAME";
    string command;
    boost::property_tree::ptree request;
    bool isRequest = true;

    try{
        clientAddress = parsed.get<std::string>("clientID");
        command = parsed.get<std::string>("command");
        nickname = parsed.get<std::string>("client");
    } catch(const boost::property_tree::ptree_error & exception){
        Logger.log("No command, clientID or client field found :" + std::string(msg->get_payload()));
        return;
    }

    Logger.log("clientID :" + clientAddress + " ; command :" + command + " ; client :" + nickname);

    try{
        request = parsed.get_child("data");
    } catch(const boost::property_tree::ptree_error &exception){
        isRequest = false;
    }

    if(command == "addClient"){
        Sender* sender = new Sender(this, clientAddress);
        clientServer->addClient(nickname, clientAddress, sender);

        Logger.log("Added client " + nickname + " for " + clientAddress);
    } else if(command == "request"){
        if(!isRequest){
            Logger.log("No request for request command found");
            return;
        }
        try {
            clientServer->getClient(clientAddress, nickname)->addRequest(request);
        } catch(const char * e){
            Logger.log("Could not find client :" + nickname);
        }

        Logger.log("Added request for" + nickname);
    } else if(command == "removeClient"){
        boost::property_tree::ptree quit;

        quit.put_child("command", boost::property_tree::ptree("disconnect"));
        quit.put_child("data", boost::property_tree::ptree("empty"));

        try {

            Client* temp = clientServer->getClient(clientAddress, nickname);

            clientServer->removeClient(clientAddress, nickname);

            temp->addRequest(quit);

        } catch(const char * e){
            Logger.log("Could not find client :" + nickname);
        }


        Logger.log("Removed client " + nickname + " for " + clientAddress);
    } else {
        Logger.log("Invalid command :" + command);
    }
}

bool ConnectionServer::sendData(string data, std::string id) {
    websocketpp:: connection_hdl hdl;
//    string id = "cid"; //TODO pu thin in data or as argument
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

    map<string, websocketpp::connection_hdl>::iterator iter = websockets.find(id);
    if (iter == websockets.end()) {
        return false;
    }

    hdl = iter->second;

    return true;
}


void ConnectionServer::start() {
    Thread = boost::thread(boost::bind(&ConnectionServer::run, this));
}
