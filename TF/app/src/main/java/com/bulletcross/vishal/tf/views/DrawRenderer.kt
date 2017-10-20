package com.bulletcross.vishal.tf.views

import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint

object DrawRenderer {
    /**
     * Draw lines to canvas
     */

    fun renderModel(canvas: Canvas, model: DrawModel, paint: Paint,
                    startLineIndex: Int) {
        //minimize distortion artifacts
        paint.isAntiAlias = true

        //get the size of the line to draw
        val lineSize = model.lineSize
        //given that size
        for (i in startLineIndex until lineSize) {
            //get the whole line from the model object
            val line = model.getLine(i)
            //set its color
            paint.color = Color.BLACK
            //get the first of many lines that make up the overall line
            val elemSize = line.elemSize
            //if its empty, skip
            if (elemSize < 1) {
                continue
            }
            // store that first line element in elem
            var elem: DrawModel.LineElem = line.getElem(0)
            //get its coordinates
            var lastX = elem.x
            var lastY = elem.y

            //for each coordinate in the line
            for (j in 0 until elemSize) {
                //get the next coordinate
                elem = line.getElem(j)
                val x = elem.x
                val y = elem.y
                //and draw the line between those two paints
                canvas.drawLine(lastX, lastY, x, y, paint)
                //store the coordinate as last and repeat
                //until the line is drawn
                lastX = x
                lastY = y
            }
        }
    }
}