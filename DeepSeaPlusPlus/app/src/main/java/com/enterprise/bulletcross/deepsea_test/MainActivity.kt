package com.enterprise.bulletcross.deepsea_test

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val input_vector = DoubleArray(4)
        input_vector[0] = 3.4
        input_vector[1] = 6.7
        input_vector[2] = 8.9
        input_vector[3] = 3.0
        // Example of a call to a native method
        val max_from_jni:Double = dummy(input_vector)
        //println(dummy(input_vector))
        sample_text.text = stringFromJNI() + max_from_jni.toString()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun dummy(inp: DoubleArray): Double

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
