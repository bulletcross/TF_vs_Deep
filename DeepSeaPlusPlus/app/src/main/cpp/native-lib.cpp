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

#define INPUT_SIZE 784
#define NUM_CLASSES 4

extern "C"
{

static const int arr[] = {INPUT_SIZE, 1024, 100, 150, 20, NUM_CLASSES};
vector<int> layer (arr, arr + sizeof(arr)/sizeof(arr[0]));

blaze::DynamicMatrix<double> output_cache(4, 1);
blaze::DynamicMatrix<double> input_cache(784, 1);

//model_param m_p = read_model("model_5.txt");
forward_param f_p(layer, 1);

JNIEXPORT void

JNICALL
Java_com_enterprise_bulletcross_deepsea_1test_MainActivity_load_weight(
        JNIEnv *env,
        jobject ) {
    //TO-DO: assignment of m_p and f_p in here

};

JNIEXPORT jint

JNICALL
Java_com_enterprise_bulletcross_deepsea_1test_MainActivity_predict_JNI(
        JNIEnv *env,
        jobject ,
        jdoubleArray inp) {
    //jsize len = env->GetArrayLength(inp);
    //jint ret = -1;
    /*jdouble *point = env->GetDoubleArrayElements(inp, 0);
    for(jint i=0;i<len;i++){
        input_cache(i,0) = point[i];
    }
    output_cache = predict(&m_p,&f_p, input_cache);
    jint ret = -1;
    double max_value = -1;
    for(int i=0;i<4;i++){
        if(max_value < output_cache(i,0)){
            max_value = output_cache(i,0);
            ret = i;
        }
    }
    env->ReleaseDoubleArrayElements(inp, point, 0);*/
    return -1;
};
}