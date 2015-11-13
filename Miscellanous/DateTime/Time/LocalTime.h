//
// Created by Wojciech Grabis on 24.10.15.
//

#ifndef FILETRADER_LOCALTIME_H
#define FILETRADER_LOCALTIME_H


#include <ctime>
#include <string>

class LocalTime {
protected:
    int hour;
    int minute;
    int second;
    int milisecond;
public:
    LocalTime(const std::tm timeStruct);
    LocalTime(const std::time_t timeStruct);
    LocalTime(const LocalTime& other);
    void change(std::tm newTime);
    void change(std::time_t newTime);
    bool operator <(LocalTime const &other);
    bool operator >(LocalTime const &other);
    LocalTime operator =(LocalTime const &other);
    bool operator ==(LocalTime const &other);
    bool operator <=(LocalTime const &other);
    bool operator >=(LocalTime const &other);
    bool operator !=(LocalTime const &other);
    static LocalTime genCurrTime();
    std::string print();
};


#endif //FILETRADER_LOCALTIME_H
