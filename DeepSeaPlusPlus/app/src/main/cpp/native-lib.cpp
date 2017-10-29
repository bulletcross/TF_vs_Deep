#include <jni.h>

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include <blaze/Math.h>

#include <deepsea/math_util.h>
#include <deepsea/network_builder.h>
#include <deepsea/prediction.h>
#include <deepsea/read_write_util.h>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_enterprise_bulletcross_deepsea_1test_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++ Native success";
    blaze::DynamicMatrix<double> A(3,2);
    return env->NewStringUTF(hello.c_str());
}
