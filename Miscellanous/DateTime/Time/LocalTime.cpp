//
// Created by Wojciech Grabis on 24.10.15.
//

#include "LocalTime.h"


LocalTime::LocalTime(const std::tm timeStruct){
    hour = timeStruct.tm_hour;
    minute = timeStruct.tm_min;
    second = timeStruct.tm_sec;
    milisecond = 0;
}

LocalTime::LocalTime(const std::time_t timeStruct){
    struct tm* timeTmpStruct;
    timeTmpStruct = std::localtime(&timeStruct);

    hour = timeTmpStruct->tm_hour;
    minute = timeTmpStruct->tm_min;
    second = timeTmpStruct->tm_sec;
    milisecond = 0;
}

LocalTime::LocalTime(const LocalTime &other) {
    hour = other.hour;
    minute = other.minute;
    second = other.second;
    milisecond = other.milisecond;
}

std::string LocalTime::print() {
    return "[" + std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second) + "." + std::to_string(milisecond) + "]";
}

void LocalTime::change(std::tm newTime){
    hour = newTime.tm_hour;
    minute = newTime.tm_min;
    second = newTime.tm_sec;
    milisecond = 0;
}

void LocalTime::change(std::time_t newTime){
    struct tm* timeTmpStruct;
    timeTmpStruct = std::localtime(&newTime);

    hour = timeTmpStruct->tm_hour;
    minute = timeTmpStruct->tm_min;
    second = timeTmpStruct->tm_sec;
    milisecond = 0;
}

bool LocalTime::operator <(LocalTime const &other){
    if(hour < other.hour)return true;
    if(hour == other.hour && minute < other.minute)return true;
    if(hour == other.hour && minute == other.minute && second < other.second)return true;
    if(hour == other.hour && minute == other.minute && second == other.second && milisecond < other.milisecond)return true;

    return false;
}

bool LocalTime::operator >(LocalTime const &other){
    if(hour > other.hour)return true;
    if(hour == other.hour && minute > other.minute)return true;
    if(hour == other.hour && minute == other.minute && second > other.second)return true;
    if(hour == other.hour && minute == other.minute && second == other.second && milisecond > other.milisecond)return true;

    return false;
}

bool LocalTime::operator ==(LocalTime const &other){
    if(hour == other.hour && minute == other.minute && second == other.second && milisecond == other.milisecond)return true;

    return false;
}

bool LocalTime::operator <=(LocalTime const &other){
    if(*this > other)return false;

    return true;
}

LocalTime LocalTime::operator=(LocalTime const &other) {
    hour = other.hour;
    minute = other.minute;
    second = other.second;
    milisecond = other.milisecond;
    return *this;
}

bool LocalTime::operator >=(LocalTime const &other){
    if(*this < other)return false;

    return true;
}

bool LocalTime::operator!=(LocalTime const &other) {
    if(*this == other)return false;

    return true;
}

LocalTime LocalTime::genCurrTime(){
    time_t currTime = std::time(NULL);

    return LocalTime(currTime);
}