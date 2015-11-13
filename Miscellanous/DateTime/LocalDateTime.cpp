//
// Created by Wojciech Grabis on 25.10.15.
//

#include "LocalDateTime.h"


LocalDateTime::LocalDateTime(tm timeStruct) : localTime(timeStruct), localDate(timeStruct){ }

LocalDateTime::LocalDateTime(time_t timeStruct) : localTime(timeStruct), localDate(timeStruct){ }

LocalDateTime::LocalDateTime(const LocalDateTime &other) : localTime(other.localTime), localDate(other.localDate) { }

void LocalDateTime::change(std::tm newTime){
    localTime.change(newTime);
    localDate.change(newTime);
}

void LocalDateTime::change(std::time_t newTime){
    localTime.change(newTime);
    localDate.change(newTime);
}

bool LocalDateTime::operator <(LocalDateTime const &other){
    if(localDate < other.localDate)return true;
    if(localDate == other.localDate && localTime < other.localTime)return true;

    return false;
}

bool LocalDateTime::operator >(LocalDateTime const &other){
    if(localDate < other.localDate)return true;
    if(localDate == other.localDate && localTime < other.localTime)return true;

    return false;
}

bool LocalDateTime::operator ==(LocalDateTime const &other){
    if(localDate == other.localDate && localTime == other.localTime)return true;

    return false;
}

LocalDateTime LocalDateTime::operator=(LocalDateTime const &other) {
    localTime = other.localTime;
    localDate = other.localDate;
    return *this;
}

bool LocalDateTime::operator <=(LocalDateTime const &other){
    return !(*this > other);
}

bool LocalDateTime::operator >=(LocalDateTime const &other){
    return !(*this < other);
}

bool LocalDateTime::operator !=(LocalDateTime const &other){
    return !(*this == other);
}

LocalDateTime LocalDateTime::genCurrDateTime(){
    time_t currTime = std::time(NULL);

    return LocalDateTime(currTime);
}
std::string LocalDateTime::print(){
    return localDate.print() + localTime.print();
}