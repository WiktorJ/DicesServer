#include <iostream>
#include <boost/thread/thread.hpp>
#include "Server/ConnectionServer/ClientServer/Client/Client.h"
#include "Server/StartUp/MainServer.h"

using namespace std;

void runCMDLine() {

    std::string command;

    MainServer Server;
    try {
        Server.start();
    } catch(const std::exception * exception){
        std::cout << "Encountered critical error" << endl;
        return;
    }

    while (1) {
        std::cin >> command;

        if (command == "p") {
            std::cout << Server.printGameInfo() << endl;
        }

        if (command == "q") {
            Server.stop();
            break;
        }
    }
}

int main() {
        runCMDLine();

        return 0;
    }
