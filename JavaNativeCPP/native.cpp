#include "TestMain.h"
#include "info.h"
#include <iostream>
using namespace std;
JNIEXPORT jobject JNICALL Java_TestMain_getInfo
  (JNIEnv *env, jclass clz, jstring str){
    jclass jniInfo = env->FindClass("info");
    //获取内部类
    if (jniInfo == 0) {
      cout << "find class info error!" << endl;
      return 0;
    }
    jmethodID jmi = env->GetMethodID(jniInfo,"<init>","()V");
    if (jmi == 0){
      cout << "get method error!" << endl;
      return 0;
    }
    jobject paramOut = env->NewObjectA(jniInfo, jmi, 0);
    const char *msg;
    msg = env->GetStringUTFChars(str,0);
    cout << msg << endl;
    jfieldID jmiName = env->GetFieldID(jniInfo,"_name","Ljava/lang/String;");
    
    env->SetObjectField(paramOut, jmiName, str); 
    //jfieldID jmiValue = env->GetFieldID(jniInfo,"_value","Ljava/lang/String;");
    
    return paramOut;

    //Get the Method ID of the constructor which takes an int    jmethodID midInit = (*env)->GetMethodID(env, cls, "<init>", "(I)V");
    //jmethodID midInit = (*env)->GetMethodID(env, cls, "<init>", "(I)V");
  }

 
