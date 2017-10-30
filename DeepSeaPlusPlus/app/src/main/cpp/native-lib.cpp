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
{
JNIEXPORT jstring

JNICALL
Java_com_enterprise_bulletcross_deepsea_1test_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++ Native success";
    blaze::DynamicMatrix<double> A(3, 2);
    return env->NewStringUTF(hello.c_str());
}


blaze::DynamicMatrix<double> output_cache(4, 1);
blaze::DynamicMatrix<double> input_cache(4, 1);

JNIEXPORT jdouble

JNICALL
Java_com_enterprise_bulletcross_deepsea_1test_MainActivity_dummy(
        JNIEnv *env,
        jobject /* this */,
        jdoubleArray inp) {

    jsize len = env->GetArrayLength(inp);
    jdouble *point = env->GetDoubleArrayElements(inp, 0);

    for(int i=0;i<4;i++){
        input_cache(i,0) = point[i];
    }
    env->ReleaseDoubleArrayElements(inp, point, 0);
    return blaze::max(input_cache);
};
}