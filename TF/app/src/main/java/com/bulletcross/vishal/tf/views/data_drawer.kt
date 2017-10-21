package com.bulletcross.vishal.tf.views

import android.content.Context
import android.graphics.*
import android.support.annotation.Nullable
import android.util.AttributeSet
import android.view.View

/**
 * Created by vishal on 21/10/17.
 */

class data_drawer: View {
    var paint: Paint = Paint()
    var data:data_recorder? = null
    var bitmap: Bitmap? = null
    var canvas: Canvas? = null

    var var_matrix: Matrix = Matrix()
    var var_invmatrix: Matrix = Matrix()
    var setup_done:Boolean = false
    var nr_drawn_lines:Int = 0

    var touch_mapper = FloatArray(2)

    constructor(context: Context, @Nullable attrs: AttributeSet): super(context, attrs) {}

    override fun onDraw(canvas_in: Canvas){
        if(data == null){
            return
        }
        if(setup_done == false){
            setup()
        }
        if(bitmap == null){
            return
        }
        var draw_line_index:Int = if(nr_drawn_lines == 0) 0 else nr_drawn_lines -1
        //Update canvas and screen (every update happens at 16ms)
        render_data_point(canvas, data, paint, draw_line_index)
        canvas_in.drawBitmap(bitmap,var_matrix,paint) //var_matrix is scaled based on data size
    }

    fun set_data(data:data_recorder){
        this.data = data
    }

    fun reset(){
        nr_drawn_lines = 0
        if(bitmap!=null){
            paint.color = Color.YELLOW
            val bitmap_height:Int = bitmap!!.height
            val bitmap_width:Int = bitmap!!.width
            canvas?.drawRect(Rect(0,0,bitmap_width,bitmap_height), paint)
        }
    }

    fun setup(){
        //Scaling
        var view_width:Float = width.toFloat()
        var view_height:Float = height.toFloat()
        var data_width:Float = 28F
        var data_height:Float = 28F

        var scale:Float = if(view_width/data_width > view_height/data_height) view_height/data_height else {view_width/data_width}
        var center_x:Float = data_width*scale / 2
        var center_y:Float = data_height*scale/2

        var_matrix.setScale(scale, scale)
        var_matrix.postTranslate(view_width/2 - center_x, view_height/2 - center_y)
        var_matrix.invert(var_invmatrix)
        setup_done = true
    }

    fun map_data_points(x:Float, y:Float, out: PointF){
        touch_mapper[0] = x
        touch_mapper[1] = y
        var_invmatrix.mapPoints(touch_mapper)
        out.x = touch_mapper[0]
        out.y = touch_mapper[1]
    }

    fun create_bitmap(){
        if(bitmap!=null){
            bitmap?.recycle()
        }
        bitmap = Bitmap.createBitmap(28, 28, Bitmap.Config.ARGB_8888)
        canvas = Canvas(bitmap)
        reset()
    }

    fun release_bitmap(){
        if(bitmap!=null){
            bitmap?.recycle()
            bitmap = null
            canvas = null
        }
        reset()
    }

    fun onResume(){
        create_bitmap()
    }

    fun onPause(){
        release_bitmap()
    }

    fun render_data_point(canvas: Canvas?, data:data_recorder?, paint: Paint?, line_index:Int){
        paint?.isAntiAlias = true
        outer_loop@for(i in line_index until data!!.get_nr_lines()){
            var data_points:data_recorder.line = data.get_line(i)
            paint?.color = Color.BLUE
            if(data_points.nr_points() < 1){
                continue@outer_loop
            }
            var prev_x:Float = data_points.get_point(0).x
            var prev_y:Float = data_points.get_point(0).y
            inner_loop@for(j in 0..data_points.nr_points()-1){
                var current_x:Float = data_points.get_point(j).x
                var current_y:Float = data_points.get_point(j).y
                canvas?.drawLine(prev_x, prev_y, current_x, current_y, paint)
                prev_x = current_x
                prev_y = current_y
            }

        }
    }
}
