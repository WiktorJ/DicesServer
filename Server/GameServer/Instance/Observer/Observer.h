//
// Created by Wojciech Grabis on 13.12.15.
//

#ifndef DICESSERVER_OBSERVER_H
#define DICESSERVER_OBSERVER_H


#include "../Client/ClientGroup.h"
#include "jni.h"
#include "JNIInstance.h"
#include "../../../Logger/LogParser.h"

class Observer {
private:
    ClientGroup& Clients;
    jobject observerObject;
    LogParser Logger;
public:
    Observer(ClientGroup& Clients, jobject gco);
    void listen();
};


#endif //DICESSERVER_OBSERVER_H
