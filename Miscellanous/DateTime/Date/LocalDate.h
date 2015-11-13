//
// Created by Wojciech Grabis on 25.10.15.
//

#ifndef FILETRADER_LOCALDATE_H
#define FILETRADER_LOCALDATE_H

#include <ctime>
#include <string>

class LocalDate {
protected:
    int day;
    int month;
    int year;
public:
    LocalDate(const std::tm timeStruct);
    LocalDate(const std::time_t timeStruct);
    LocalDate(const LocalDate& other);
    void change(std::tm newTime);
    void change(std::time_t newTime);
    bool operator <(LocalDate const &other);
    bool operator >(LocalDate const &other);
    bool operator ==(LocalDate const &other);
    bool operator <=(LocalDate const &other);
    bool operator >=(LocalDate const &other);
    bool operator !=(LocalDate const &other);
    LocalDate operator =(LocalDate const &other);
    static LocalDate genCurrDate();
    std::string print();
};


#endif //FILETRADER_LOCALDATE_H
