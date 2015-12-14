//
// Created by Wojciech Grabis on 14.12.15.
//

#ifndef DICESSERVER_REQUESTQUEUE_H
#define DICESSERVER_REQUESTQUEUE_H


#include <vector>
#include <boost/thread/pthread/mutex.hpp>
#include <boost/thread/pthread/condition_variable.hpp>
#include "../Instance/Client/ClientMovement.h"

class RequestQueue {
private:
    std::vector<ClientMovement> Requests;
    boost::mutex Mutex;
    boost::condition_variable Condition;
    bool empty;
public:
    RequestQueue();
    RequestQueue(const RequestQueue &other);
    std::vector<ClientMovement> getRequests();
    void addRequest(ClientMovement Request);

};


#endif //DICESSERVER_REQUESTQUEUE_H
