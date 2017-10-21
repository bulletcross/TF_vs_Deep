package com.bulletcross.vishal.tf

import android.graphics.PointF
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.MotionEvent
import android.view.View
import android.widget.Button
import android.widget.TextView
import com.bulletcross.vishal.tf.views.data_drawer
import com.bulletcross.vishal.tf.views.data_recorder

class MainActivity : AppCompatActivity(), View.OnClickListener,  View.OnTouchListener{
    //Layout elements
    var button_benchmark:Button? = null
    var button_clear:Button? = null
    var button_predict:Button? = null
    var text_benchmark: TextView? = null
    var text_accuracy: TextView? = null
    var text_predict: TextView? = null
    //Listeners
    var data_rec: data_recorder? = null
    var data_draw: data_drawer? = null

    var temp_x:Float = 0.0F
    var temp_y:Float = 0.0F
    var temp_point = PointF()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        //Obtain by ID
        button_benchmark = findViewById(R.id.button)
        button_clear = findViewById(R.id.button3)
        button_predict = findViewById(R.id.button2)
        text_benchmark = findViewById(R.id.textView2)
        text_accuracy = findViewById(R.id.textView4)
        text_predict = findViewById(R.id.textView5)

        data_draw = findViewById(R.id.draw)
        data_rec = data_recorder()

        data_draw?.set_data(data_rec!!)
        data_draw?.setOnTouchListener(this)
        button_benchmark?.setOnClickListener(this)
        button_clear?.setOnClickListener(this)
        button_predict?.setOnClickListener(this)

    }

    override fun onResume(){
        data_draw?.onResume()
        super.onResume()
    }

    override fun onPause(){
        data_draw?.onPause()
        super.onPause()
    }

    override fun onClick(v:View){
        if(v.getId() == R.id.button){
            //Run Benchmark

        }
        else if(v.getId() == R.id.button3){
            //Clear data_draw view
            data_rec?.clear_lines()
            data_draw?.reset()
            data_draw?.invalidate() //Force redraw on screen
            text_accuracy?.setText("C")
        }
        else if(v.getId() == R.id.button2){
            //Run prediction model on view data
        }
    }

    override fun onTouch(v:View, event: MotionEvent):Boolean{
        var action = event.action
        if(action == MotionEvent.ACTION_DOWN){
            temp_x = event.getX()
            temp_y = event.getY()
            data_draw?.map_data_points(temp_x, temp_y, temp_point)
            data_rec?.record_touch(temp_point.x, temp_point.y)
            return true
        }
        else if(action == MotionEvent.ACTION_MOVE){
            var x:Float = event.getX()
            var y:Float = event.getY()
            data_draw?.map_data_points(temp_x, temp_y, temp_point)
            data_rec?.record_motion(temp_point.x, temp_point.y)
            temp_x = x
            temp_y = y
            return true
        }
        else if(action == MotionEvent.ACTION_UP){
            data_rec?.finalize_motion()
            return true
        }
        return false
    }

}
