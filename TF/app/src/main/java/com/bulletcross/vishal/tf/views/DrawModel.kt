package com.bulletcross.vishal.tf.views

import java.util.ArrayList

class DrawModel//given a set 28 by 28 sized window
(val width: Int  // pixel width = 28
 , val height: Int // pixel height = 28
) {


    private var mCurrentLine: Line? = null

    //so a model consits of lines which consists of elements
    //a line begins when a user starts drawing and ends when
    //they lift their finger up
    private val mLines = ArrayList<Line>()

    val lineSize: Int
        get() = mLines.size

    //initialize beginning of the line coordinate
    class LineElem//internal repreesntation for manipulation
    private constructor(var x: Float, var y: Float)

    //for a single line
    class Line private constructor() {
        //a line consits of a set of elements (small parts of a line)
        private val elems = ArrayList<LineElem>()

        val elemSize: Int
            get() = elems.size

        //add, get, and get index of an element
        private fun addElem(elem: LineElem) {
            elems.add(elem)
        }

        fun getElem(index: Int): LineElem {
            return elems[index]
        }
    }

    //start drawing line and add it to memory
    fun startLine(x: Float, y: Float) {
        mCurrentLine = Line()
        mCurrentLine!!.addElem(LineElem(x, y))
        mLines.add(mCurrentLine)
    }

    fun endLine() {
        mCurrentLine = null
    }

    fun addLineElem(x: Float, y: Float) {
        if (mCurrentLine != null) {
            mCurrentLine!!.addElem(LineElem(x, y))
        }
    }

    fun getLine(index: Int): Line {
        return mLines[index]
    }

    fun clear() {
        mLines.clear()
    }
}