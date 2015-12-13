#include <iostream>
#include <boost/array.hpp>
#include <jni.h>
#include "JNI-test/SimpleInstanceJNI.h"
#include "GameServer/JNIInstance.h"
#include "GameServer/Observer.h"
#include "Server/ConnectionServer/ClientServer/Client/Client.h"
#include "Server/GameServer/Server/Client/WaitingRoom.h"
#include "Server/GameServer/Instance/Client/ClientGroup.h"

using namespace std;

int main(){


    //boost::array<int, 4> arr = {{1,2,3,4}};
    //cout << "hi" << arr[0];
    JNIInstance instanceJNI ("xd");
    Observer o (&instanceJNI);
    Observer o2 (&instanceJNI);
    o.listen(1);
    o2.listen(2);
//    instanceJNI.runSimpleWriter("/home/wiktor/Documents/try_jni");
    instanceJNI.close();


    Client* test1 = new Client("test1");
    Client* test2 = new Client("test2");
    Client* test3 = new Client("test3");

    WaitingRoom testRoom;

    testRoom.addClient(test1);
    testRoom.addClient(test2);

    vector<ClientMovement> tescik = testRoom.getRequests();

    for(vector<ClientMovement>::iterator it = tescik.begin(); it != tescik.end(); it++) cout << (*it).getUsername() << endl;
    ClientGroup testGroup(testRoom);
    testGroup.addSubscriber(test3);



    testGroup.removeSubscriber("test3");

    cout <<"heheszki"<<endl;

    tescik = testRoom.getRequests();

    for(vector<ClientMovement>::iterator it = tescik.begin(); it != tescik.end(); it++) cout << (*it).getUsername() << endl;

    //SimpleInstanceJNI instanceJNI;
    //instanceJNI.runSimpleWriter("/home/wiktor/pojebanyichuj");
    //instanceJNI.close();
    return 0;
}
