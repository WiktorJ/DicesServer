//
// Created by Wojciech Grabis on 14.12.15.
//

#include <boost/thread/lock_guard.hpp>
#include "RequestQueue.h"

void RequestQueue::addRequest(ClientMovement Request) {
    Requests.push_back(Request);
    {
        boost::lock_guard<boost::mutex> lock(Mutex);
        empty = false;
    }
    Condition.notify_one();

}

std::vector<ClientMovement> RequestQueue::getRequests() {
    boost::unique_lock<boost::mutex> lock(Mutex);
    while(empty)
    {
        Condition.wait(lock);
    }
    std::vector<ClientMovement> result = Requests;
    Requests.clear();
    empty = true;

    return result;
}

RequestQueue::RequestQueue() {
    empty = true;
}


RequestQueue::RequestQueue(const RequestQueue &other) : Requests(other.Requests){

}
