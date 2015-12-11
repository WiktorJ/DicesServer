#include <iostream>
#include <boost/array.hpp>
#include <jni.h>
#include "JNI-test/SimpleInstanceJNI.h"
#include "GameServer/JNIInstance.h"
#include "GameServer/Observer.h"

using namespace std;

int main(){


    //boost::array<int, 4> arr = {{1,2,3,4}};
    //cout << "hi" << arr[0];
    JNIInstance instanceJNI ("xd");
    Observer o (&instanceJNI);
    Observer o2 (&instanceJNI);
    o.listen(1);
    o2.listen(2);
//    instanceJNI.runSimpleWriter("/home/wiktor/Documents/try_jni");
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