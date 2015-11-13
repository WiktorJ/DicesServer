//
// Created by Wojciech Grabis on 25.10.15.
//

#ifndef FILETRADER_LOCALDATETIME_H
#define FILETRADER_LOCALDATETIME_H


#include "Time/LocalTime.h"
#include "Date/LocalDate.h"

class LocalDateTime {
private:
    LocalTime localTime;
    LocalDate localDate;
public:
    LocalDateTime(tm timeStruct);
    LocalDateTime(time_t timeStruct);
    LocalDateTime(const LocalDateTime &other);
    void change(std::tm newTime);
    void change(std::time_t newTime);
    bool operator <(LocalDateTime const &other);
    bool operator >(LocalDateTime const &other);
    bool operator ==(LocalDateTime const &other);
    bool operator <=(LocalDateTime const &other);
    LocalDateTime operator =(LocalDateTime const &other);
    bool operator >=(LocalDateTime const &other);
    bool operator !=(LocalDateTime const &other);
    static LocalDateTime genCurrDateTime();
    std::string print();
};


#endif //FILETRADER_LOCALDATETIME_H
