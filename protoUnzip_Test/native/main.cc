//corpize company , writen by guxx
#include <iostream>

#include "testData.pb.h"
#include "info.h"
#include "TestMain.h"

using namespace org;
using namespace std;

//public class testInfo{
//  public std::string name;
//  public std::string key;
//  public std::string value;
//}

//testInfo deserializeFromChars(char *in);

//testInfo deserializeFromChars(char *in){
//  testInfo ti;
//  ti.name = "tName";
//  ti.key = "tKey";
//  ti.value = "tValue";
//  return ti;
//}


/******
 **
 **

int main(){
  cout << "yes, proto buf cpp" << endl;
  org::apache::metis::LogGroup *l = new org::apache::metis::LogGroup();
  l->set_name("name");
  org::apache::metis::LogTag *lt = l->add_tags();
  lt->set_value("value");
  lt->set_key("key");
  //cout << l->DebugString() << endl;
  int length = l->ByteSize();
  char *buf = new char[length];
  l->SerializeToArray(buf, length);
  for(int i = 0; i < length; ++i)
    cout << "buf char[" << i << "] is : " << int(buf[i]) << endl;
  
  cout << "unzip result:"<< endl;
  org::apache::metis::LogGroup l2;
  l2.ParseFromArray(buf, length);
  cout << "name : " << l2.name() << endl;
  cout << "    |" << endl;
  cout << "    |" << endl;
  cout << "    ______ value: " << l2.tags(0).value() << endl;
  delete buf;
  delete l;

  return 0;  
}
 **
 **
 ******/

JNIEXPORT jstring JNICALL Java_TestMain_getWords(JNIEnv * env, jclass){
  org::apache::metis::LogGroup *l = new org::apache::metis::LogGroup();
  l->set_name("name");
  org::apache::metis::LogTag *lt = l->add_tags();
  lt->set_value("value");
  lt->set_key("key");
  int length = l->ByteSize();
  char *buf = new char[length];
  l->SerializeToArray(buf, length);
  cout << "buf is : " << buf << endl;
  jbyteArray bytes = (env)->NewByteArray(strlen(buf));
  (env)->SetByteArrayRegion(bytes, 0, strlen(buf), (jbyte*) buf);
  delete l;
  jclass strClass = (env)->FindClass("Ljava/lang/String;");
  jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
  jstring encoding = (env)->NewStringUTF("GB2312");
  return (jstring) (env)->NewObject(strClass, ctorID, bytes, encoding);
}

JNIEXPORT jobject JNICALL Java_TestMain_unzipInfo(JNIEnv * env, jclass clz, jstring str){
  org::apache::metis::LogGroup lg;

  char* rtn = NULL;
  jclass clsstring = env->FindClass("java/lang/String");
  jstring strencode = env->NewStringUTF("GB2312");
  jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
  jbyteArray barr = (jbyteArray) env->CallObjectMethod(str, mid, strencode);
  jsize alen = env->GetArrayLength(barr);
  jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
  if (alen > 0) {
    rtn = (char*) malloc(alen + 1);
    memcpy(rtn, ba, alen);
    rtn[alen] = 0;
  }
  env->ReleaseByteArrayElements(barr, ba, 0);

  lg.ParseFromArray(rtn, alen + 1);
// 压力测试时请屏蔽下面的print语句
//  cout << " lg name : " << lg.name() << endl; 
  delete rtn;

  return 0;  


}

JNIEXPORT void JNICALL Java_TestMain_unzipNull
  (JNIEnv *, jclass){
  org::apache::metis::LogGroup *l = new org::apache::metis::LogGroup();
  l->set_name("name");
  org::apache::metis::LogTag *lt = l->add_tags();
  lt->set_value("value");
  lt->set_key("key");
  int length = l->ByteSize();
  char *buf = new char[length];
  l->SerializeToArray(buf, length);
  org::apache::metis::LogGroup lg;
  lg.ParseFromArray(buf, length);
// 压力测试时请屏蔽下面的print语句


  
  
  
  delete l;


}




