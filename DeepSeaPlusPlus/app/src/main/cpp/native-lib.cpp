#include <jni.h>
#include <string>
#include <blaze/Math.h>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_enterprise_bulletcross_deepsea_1test_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    blaze::DynamicMatrix<double> A(3,2);
    return env->NewStringUTF(hello.c_str());
}
