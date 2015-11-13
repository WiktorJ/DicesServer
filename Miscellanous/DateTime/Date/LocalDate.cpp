//
// Created by Wojciech Grabis on 25.10.15.
//

#include "LocalDate.h"

LocalDate::LocalDate(const std::tm timeStruct){
    day = timeStruct.tm_mday;
    month = timeStruct.tm_mon;
    year = 1900 + timeStruct.tm_year;

}

LocalDate::LocalDate(const LocalDate &other) {
    day = other.day;
    month = other.month;
    year = other.year;
}

LocalDate::LocalDate(const std::time_t timeStruct){
    struct tm* timeTmpStruct;
    timeTmpStruct = std::localtime(&timeStruct);

    day = timeTmpStruct->tm_mday;
    month = timeTmpStruct->tm_mon;
    year = 1900 + timeTmpStruct->tm_year;
}

void LocalDate::change(std::tm newTime){
    day = newTime.tm_mday;
    month = newTime.tm_mon;
    year = 1900 + newTime.tm_year;
}

void LocalDate::change(std::time_t newTime){
    struct tm* timeTmpStruct;
    timeTmpStruct = std::localtime(&newTime);

    day = timeTmpStruct->tm_mday;
    month = timeTmpStruct->tm_mon;
    year = 1900 + timeTmpStruct->tm_year;
}

LocalDate LocalDate::operator=(LocalDate const &other) {
    day = other.day;
    month = other.month;
    year = other.year;
    return *this;
}

bool LocalDate::operator <(LocalDate const &other){
    if(year < other.year)return true;
    if(year == other.year && month < other.month)return true;
    if(year == other.year && month == other.month && day < other.day)return true;

    return false;
}

bool LocalDate::operator >(LocalDate const &other){
    if(year > other.year)return true;
    if(year == other.year && month > other.month)return true;
    if(year == other.year && month == other.month && day > other.day)return true;

    return false;
}

bool LocalDate::operator ==(LocalDate const &other){
    if(year == other.year && month == other.month && day == other.day)return true;

    return false;
}

bool LocalDate::operator <=(LocalDate const &other){
    return !(*this > other);
}

bool LocalDate::operator >=(LocalDate const &other){
    return !(*this < other);
}

bool LocalDate::operator!=(LocalDate const &other) {
    return !(*this == other);
}

LocalDate LocalDate::genCurrDate(){
    time_t currTime = std::time(NULL);

    return LocalDate(currTime);
}
std::string LocalDate::print(){
    return "[" + std::to_string(day) + ":" + std::to_string(month) + ":" + std::to_string(year) + "]";
}