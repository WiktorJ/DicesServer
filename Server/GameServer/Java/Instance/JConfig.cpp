//
// Created by Wojciech Grabis on 21.12.15.
//

#include <iostream>
#include "JConfig.h"
#include "../Exception/JNIException.h"

JConfig &JConfig::getInstance() {
    static JConfig instance;
    return instance;
}

JConfig::JConfig() {
    Set = false;

//    std::cout << "Write jar path" << std::endl;
//    std::cin >> JARPath;
    JARPath = "//home/wg/Github/DicesServer/ControllersContainer/target/classes/.:/home/wg/Github/DicesServer/ControllersContainer/target/lib/json-20151123.jar";

//    std::cout << "Write observer package" << std::endl;
//    std::cin >> ObserverPackage;
    ObserverPackage  = "to2/ds/game/controllers/Observer";

//    std::cout << "Write observerImpl package" << std::endl;
//    std::cin >> ObserverPackage;
    ObserverImplPackage  = "to2/ds/game/controllers/ObserverImpl";

//    std::cout << "Write factory package" << std::endl;
//    std::cin >> FactoryPackage;
    FactoryPackage = "to2/ds/game/controllers/MockedGameFactory";

//    std::cout << "Write controller package" << std::endl;
//    std::cin >> ControllerPackage;
    ControllerPackage = "to2/ds/game/controllers/MockedGameController";

    test();
}

std::string JConfig::getJarPath() {
    if(Set) return JARPath;
    throw new JNIException;
}

std::string JConfig::getObserverPackage() {
    if(Set) return ObserverPackage;
    throw new JNIException;
}
std::string JConfig::getObserverImplPackage() {
    if(Set) return ObserverImplPackage;
    throw new JNIException;
}

std::string JConfig::getControllerPackage() {
    if(Set) return ControllerPackage;
    throw new JNIException;
}

std::string JConfig::getFactoryPackage() {
    if(Set) return FactoryPackage;
    throw new JNIException;
}

JConfig::~JConfig() {

}

void JConfig::test() {
    Set = true;
}
