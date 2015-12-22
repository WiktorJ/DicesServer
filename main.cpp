#include <iostream>
#include <boost/thread/thread.hpp>
#include "Server/ConnectionServer/ClientServer/Client/Client.h"
#include "Server/StartUp/MainServer.h"
#include "Server/ConnectionServer/ClientServer/ConnectionServer.h"

using namespace std;

void tester() {


    std::string command;

    MainServer Server;

    std::vector<Client *> clients;

    while (1) {
        std::cin >> command;

        if (command == "p") {
            std::cout << Server.printGameInfo() << endl;
        }

//        if (command == "c") {
//            std::string newUser;
//            std::cin >> newUser;
//            Client *newClient = new Client(newUser);
//            clients.push_back(newClient);
//
//            Server.temporaryClient(newClient);
//        }

        if (command == "j") {
            std::string name;
            std::cin >> name;

            for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++) {
                if ((*it)->getUsername() == name) {
                    cout << "Write json path" << endl;

                    std::string path;

                    boost::property_tree::ptree pt;
                    cin >> path;
                    try {
                        boost::property_tree::read_json(path, pt);


                    } catch (const boost::property_tree::ptree_error &exception) {
                        cout << "json error";
                        continue;
                    }
                    (*it)->addRequest(pt);

                }
            }

        }

        if (command == "q") {
            Server.stop();
            break;
        }
    }
}

//void tester(){
//
//
//    std::string command;
//
//    MainServer Server;
//
//    std::vector<Client* > clients;
//
//    while(1){
//        std::cin >> command;
//
//        if(command == "c"){
//            std::string newUser;
//            std::cin >> newUser;
//
//            Client* newClient = new Client(newUser);
//            clients.push_back(newClient);
//
//            Server.temporaryClient(newClient);
//        }
//
//        if(command == "j"){
//            std::string name;
//            std::cin >> name;
//
//            for(std::vector<Client* >::iterator it = clients.begin(); it != clients.end(); it++){
//                if((*it)->getUsername() == name){
//                    cout << "Write json path" << endl;
//
//                    std::string path;
//
//                    boost::property_tree::ptree pt;
//                    cin >> path;
//
//                    boost::property_tree::read_json(path, pt);
//                }
//            }
//
//        }
//
//        if(command == "q"){
//            break;
//        }
//    }
//}


int main() {

//    try {
//        WaitingRoom * wr = new WaitingRoom();
//        ConnectionServer server_instance(wr);
//        server_instance.init(9020);
//        boost::thread t = boost::thread(boost::bind(&ConnectionServer::run, &server_instance));
//        t.join();
//    } catch (websocketpp::exception const &e) {
//        std::cout << e.what() << std::endl;
//    }

        tester();
//    Client* test1 = new Client("test1");
////    Client* test2 = new Client("test2");
////    Client* test3 = new Client("test3");
////
//    WaitingRoom testRoom;
////
//    testRoom.addClient(test1);
//    GameFactory gameFactory;
//    boost::property_tree::ptree newData;
//    std::string cmd = "xD";
//    newData.put_child("command", boost::property_tree::ptree(cmd));
//    GameInstance *gameInstance = gameFactory.createGame(newData, testRoom);
//    gameInstance->start();
        //boost::array<int, 4> arr = {{1,2,3,4}};
        //cout << "hi" << arr[0];
//    JNIInstance instanceJNI ("xd");
//    Observer o (&instanceJNI);
//
//    Observer o2 (&instanceJNI);
//    boost::thread t1(&Observer::listen, &o, 1);
//    boost::thread t2(&Observer::listen, &o2, 2);
//    t1.join();
//    t2.join();

//    o.listen(1);

//    o2.listen(2);
//    instanceJNI.runSimpleWriter("/home/wiktor/Documents/try_jni");
//    instanceJNI.close();
//
//
//    Client* test1 = new Client("test1");
//    Client* test2 = new Client("test2");
//    Client* test3 = new Client("test3");
//
//    WaitingRoom testRoom;
//
//    testRoom.addClient(test1);
//    testRoom.addClient(test2);
//
//    vector<ClientMovement> tescik = testRoom.getRequests();
//
//    for(vector<ClientMovement>::iterator it = tescik.begin(); it != tescik.end(); it++) cout << (*it).getUsername() << endl;
//    ClientGroup testGroup(testRoom);
//    testGroup.addSubscriber(test3);
//
//
//
//    testGroup.removeSubscriber("test3");
//
//    cout <<"heheszki"<<endl;
//
//    tescik = testRoom.getRequests();
//
//    for(vector<ClientMovement>::iterator it = tescik.begin(); it != tescik.end(); it++) cout << (*it).getUsername() << endl;
//
//    //SimpleInstanceJNI instanceJNI;
//    //instanceJNI.runSimpleWriter("/home/wiktor/pojebanyichuj");
//    //instanceJNI.close();
        return 0;
    }
