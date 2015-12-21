//
// Created by Wojciech Grabis on 21.12.15.
//

#ifndef DICESSERVER_JCONFIG_H
#define DICESSERVER_JCONFIG_H

#include <string>

class JConfig {
private:
    JConfig();
    ~JConfig();

    bool Set;
    std::string JARPath;
    std::string ObserverPackage;
    std::string ControllerPackage;
    std::string FactoryPackage;

    void test();
public:
    static JConfig& getInstance();
    std::string getJarPath();
    std::string getObserverPackage();
    std::string getControllerPackage();
    std::string getFactoryPackage();

};


#endif //DICESSERVER_JCONFIG_H
