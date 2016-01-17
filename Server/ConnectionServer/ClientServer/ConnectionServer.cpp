//
// Created by wiktor on 20.12.15.
//

#include "ConnectionServer.h"
#include "../Connector/Network/Sender.h"
#include "Deserializer/MessageHandle.h"
#include "Deserializer/Exception/ConnMessageException.h"
#include "Deserializer/Exception/ClientMessageException.h"
#include "Exception/NameTakenException.h"
#include "Serializer/ConnectorResponseSerializer.h"
#include "Exception/ConnectorNotFoundException.h"
#include "Exception/ClientNotFoundException.h"

using namespace std;



ConnectionServer::ConnectionServer(WaitingRoom *waitingRoom) : Logger("ConnectionServer") {
    clientServer = new ClientServer(waitingRoom);
}

bool ConnectionServer:: init(int port) {
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
    Logger.log("New validate connection");
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

    Logger.log("Adding new endpoint");
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
    Logger.log("websocket closing");

    std::map<string, websocketpp::connection_hdl>::iterator it;

    std::string logResult;
    for(it = websockets.begin(); it != websockets.end(); it++){
        if(server.get_con_from_hdl((*it).second) == server.get_con_from_hdl(hdl)){
            std::string id = (*it).first;
            websockets.erase(it);

            std::vector<Client *> Clients = clientServer->getClientList(id);
            clientServer->removeClientEndpoint(id);

            for(std::vector<Client *>::iterator tmp = Clients.begin(); tmp != Clients.end(); tmp++){
                boost::property_tree::ptree quit;

                quit.put_child("command", boost::property_tree::ptree("disconnect"));
                quit.put_child("data", boost::property_tree::ptree("empty"));


                logResult += (*tmp)->getUsername() + ", ";
                (*tmp)->addRequest(quit);
            }

            websocketpp::lib::error_code ec;
            string data = "";
            server.close(it->second, websocketpp::close::status::normal, data, ec); // send text message.
            if (ec) {
                Logger.log("error in ConnectionServer:stop()");
                Logger.log(ec.message());
            }


            Logger.log("Removed endpoint :" + id + " clients : {" + logResult + "}");
            return;

        }
    }

}


void ConnectionServer::on_message(websocketpp::connection_hdl hdl,  websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
    try {
        MessageHandle Message(msg->get_payload());

        switch(Message.getCommand()){
            case ConnCommand::ADDPLAYER: {
                try {
                    Sender *sender = new Sender(this, Message.getClientID());
                    try {
                        clientServer->addClient(Message.getClientName(), Message.getClientID(), sender);

                        Logger.log("Added client " + Message.getClientName() + " for " + Message.getClientID());

                        sender->send(ConnectorResponseSerializer::serializeType(ConnectorResponseSerializer::serializeResponse("addPlayer", status::SUCCESS)));
                    } catch(const NameTakenException& exception2){
                        Logger.log("Could not add client " + Message.getClientName() + " for " + Message.getClientID() + " reason: NAME TAKEN");

                        sender->send(ConnectorResponseSerializer::serializeType(ConnectorResponseSerializer::serializeResponse("addPlayer", status::FAILURE)));
                    } catch(const ConnectorNotFoundException& exception3){
                        Logger.log("Clientaddress not found");
                    }
                }  catch(const ClientMessageException& exception1){
                    Logger.log("Invalid client message" + std::string(msg->get_payload()));
                }
            }
            case ConnCommand::REMOVEPLAYER: {
                boost::property_tree::ptree quit;

                quit.put_child("command", boost::property_tree::ptree("disconnect"));
                quit.put_child("data", boost::property_tree::ptree("empty"));

                try {
                    Sender tempSender(this, Message.getClientID());
                    try {

                        Client* temp = clientServer->getClient(Message.getClientID(), Message.getClientName());

                        clientServer->removeClient(Message.getClientID(), Message.getClientName());

                        temp->addRequest(quit);

                        tempSender.send(ConnectorResponseSerializer::serializeType(ConnectorResponseSerializer::serializeResponse("removePlayer", status::SUCCESS)));
                    } catch(const ClientNotFoundException){
                        tempSender.send(ConnectorResponseSerializer::serializeType(ConnectorResponseSerializer::serializeResponse("removePlayer", status::FAILURE)));
                    }  catch(const ConnectorNotFoundException& exception3){
                        Logger.log("Clientaddress not found");
                    }
                } catch(const ClientMessageException& exception1){
                    Logger.log("Invalid client message" + std::string(msg->get_payload()));
                }
            }
            case ConnCommand::QUIT: {
                std::string logResult = "";

                try {
                    std::vector<Client *> Clients = clientServer->getClientList(Message.getClientID());
                    clientServer->removeClientEndpoint(Message.getClientID());


                    for (std::vector<Client *>::iterator tmp = Clients.begin(); tmp != Clients.end(); tmp++) {
                        boost::property_tree::ptree quit;

                        quit.put_child("command", boost::property_tree::ptree("disconnect"));
                        quit.put_child("data", boost::property_tree::ptree("empty"));


                        logResult += (*tmp)->getUsername() + ", ";
                        (*tmp)->addRequest(quit);
                    }

                    websocketpp::lib::error_code ec;
                    string data = "";
                    server.close(websockets.find(Message.getClientID())->second, websocketpp::close::status::normal, data,
                                 ec); // send text message.
                    if (ec) {
                        Logger.log("error in ConnectionServer:stop()");
                        Logger.log(ec.message());
                    }

                    websockets.erase(websockets.find(Message.getClientID()));

                    Logger.log("Shutting endpoint :" + Message.getClientID() + " clients : {" + logResult + "}");
                } catch(const ConnectorNotFoundException& exception2){
                    Logger.log("Could not shut down endpoint (Clientaddress not found)");
                }

            }
            case ConnCommand::REQUEST: {
                try {
                    Sender tempSender(this, Message.getClientID());
                    try {
                        clientServer->getClient(Message.getClientID(), Message.getClientName())->addRequest(Message.getClientRequest());
                    } catch (const ClientNotFoundException) {
                        tempSender.send(ConnectorResponseSerializer::serializeType(
                                ConnectorResponseSerializer::serializeResponse("request", status::FAILURE)));
                    } catch (const ConnectorNotFoundException &exception3) {
                        Logger.log("Clientaddress not found");
                    }
                } catch(const ClientMessageException& exception1){
                    Logger.log("Invalid client message" + std::string(msg->get_payload()));
                }
            }
            default:{
                Sender tempSender(this, Message.getClientID());
                tempSender.send(ConnectorResponseSerializer::serializeType(ConnectorResponseSerializer::serializeResponse("unknown", status::FAILURE)));

                Logger.log("Invalid command");
            }

        }
    } catch(const ConnMessageException& exception){
        Logger.log("Invalid message" + std::string(msg->get_payload()));
    }

}

bool ConnectionServer::sendData(string data, std::string id) {
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
