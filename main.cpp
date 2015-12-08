#include <iostream>
#include <boost/array.hpp>
#include <jni.h>
#include "JNI-test/SimpleInstanceJNI.h"

using namespace std;

int main(){


    //boost::array<int, 4> arr = {{1,2,3,4}};
    //cout << "hi" << arr[0];
    SimpleInstanceJNI instanceJNI;
    instanceJNI.runSimpleWriter("/home/wiktor/Documents/try_jni");
    instanceJNI.close();
    return 0;
}

//
//SimpleInstanceJNI* instanceJNI[10];
//
//for(int i = 0; i < 10; i++) {
//try{
//instanceJNI[i] = new SimpleInstanceJNI;
//}catch(const char* e){
//printf("%d : %s", i , e);
//return 1;
//}
//
//instanceJNI[i]->runSimpleWriter("/home/wiktor/Documents/try_jni" + i);
//}
//
//
//for(int i = 0; i < 10; i++)
//instanceJNI[i]->close();