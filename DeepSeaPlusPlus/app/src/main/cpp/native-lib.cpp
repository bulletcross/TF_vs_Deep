#include <jni.h>
#include <string>
#include <blaze/Math.h>
//#include <boost/regex.hpp>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_enterprise_bulletcross_deepsea_1test_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++ Native";
    blaze::DynamicMatrix<double> A(3,2);
    //boost::regex example_variable;
    return env->NewStringUTF(hello.c_str());
}
