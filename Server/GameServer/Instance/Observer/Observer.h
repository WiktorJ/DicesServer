//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_OBSERVER_H
#define DICESSERVER_OBSERVER_H


#include "../Client/ClientGroup.h"
#include "jni.h"
#include "../../Java/Instance/JNIInstance.h"

class Observer {
private:
    ClientGroup& Clients;
public:
    Observer(ClientGroup& Clients);
    void listen();
};


#endif //DICESSERVER_OBSERVER_H
