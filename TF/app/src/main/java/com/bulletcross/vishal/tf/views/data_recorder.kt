package com.bulletcross.vishal.tf.views

/**
 * Created by vishal on 21/10/17.
 */
class data_recorder {
    class point{
        var x: Float = 0F;
        var y: Float = 0F;
        constructor(x: Float, y: Float){
            this.x = x
            this.y = y
        }
    }

    class line{
        var line_array = mutableListOf<point>()
        fun line(){}
        fun add_point(p:point):Unit{
            line_array.add(p)
        }
        fun nr_points():Int{
            return line_array.size
        }
        fun get_point(index:Int):point{
            return line_array.get(index)
        }
    }

    //Variables to record data required for prediction
    var temp_line:line = line()
    var width:Int = 0
    var height:Int = 0
    var all_lines = mutableListOf<line>()

    fun record_touch(x:Float, y:Float):Unit{
        temp_line = line()
        var p = point(x,y)
        temp_line.add_point(p)
        all_lines.add(temp_line)
    }

    fun record_motion(x:Float, y:Float):Unit{
        if(temp_line!=null){
            var p = point(x,y)
            temp_line.add_point(p)
        }
    }

    fun finalize_motion():Unit{
        temp_line = line()
    }

    //Other helper functions
    fun get_nr_lines():Int{
        return all_lines.size
    }

    fun get_line(index:Int):line{
        return all_lines[index]
    }

    fun clear_lines():Unit{
        all_lines.clear()
    }
}