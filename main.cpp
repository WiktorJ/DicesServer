#include <iostream>
#include <boost/array.hpp>
#include <jni.h>
#include "JNI-test/SimpleInstanceJNI.h"
#include "Server/ConnectionServer/ClientServer/Client/Client.h"

using namespace std;

int main(){


    //boost::array<int, 4> arr = {{1,2,3,4}};
    //cout << "hi" << arr[0];


    SimpleInstanceJNI instanceJNI;
    instanceJNI.runSimpleWriter("/home/wiktor/pojebanyichuj");
    instanceJNI.close();
    return 0;
}
