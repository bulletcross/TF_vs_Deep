package com.enterprise.bulletcross.deepsea_test.inference

/**
 * Created by vishal on 30/10/17.
 */
class predictor {
    //external fun stringFromJNI(): String
    //external fun dummy(inp: DoubleArray): Double
    external fun loadweight()
    external fun predictJNI(inp: DoubleArray):Int


    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
    fun initialize_weights(){
        loadweight()
    }
    fun predict(input: DoubleArray):Int{
        var ret_symbol = -1;
        ret_symbol = predictJNI(input)
        return ret_symbol;
    }
}