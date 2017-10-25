package com.bulletcross.vishal.tf.inference
import android.content.Context;
import android.content.res.AssetManager;
import org.tensorflow.contrib.android.TensorFlowInferenceInterface;
import java.lang.System.loadLibrary

/**
 * Created by vishal on 25/10/17.
 */
class predictor(c:Context) {
    var inference_interface:TensorFlowInferenceInterface? = null
    var model_file:String = "file:///android_asset/optimized_model_1.pb"
    var input_name:String = "input/X_INPUT"
    var output_name:String = "layer_5/softmax_output"
    var output_nodes:Array<String> = Array(1,{"layer_5/softmax_output"})
    var input_size:LongArray = longArrayOf(1,784)
    var output_size:Int = 4
    var asset_manager:AssetManager? = null

    //Contructor
    init{
        this.asset_manager = c.assets
        inference_interface = TensorFlowInferenceInterface(asset_manager, model_file)
        loadLibrary("tensorflow_inference");
    }

    fun prediction_probability(input:FloatArray):FloatArray{
        var ret:FloatArray = floatArrayOf(0.0F, 0.0F, 0.0F, 0.0F)
        inference_interface?.feed(input_name,input, 1,784L)
        inference_interface?.run(output_nodes)
        inference_interface?.fetch(output_name,ret)
        return ret
    }
}