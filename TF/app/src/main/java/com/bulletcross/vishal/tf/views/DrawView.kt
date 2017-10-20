package com.bulletcross.vishal.tf.views

import android.content.Context
import android.graphics.Bitmap
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Matrix
import android.graphics.Paint
import android.graphics.PointF
import android.graphics.Rect
import android.util.AttributeSet
import android.view.View

class DrawView(context: Context, attrs: AttributeSet?) : View(context, attrs) {

    private val mPaint = Paint()
    private var mModel: DrawModel? = null

    // 28x28 pixel Bitmap
    private var mOffscreenBitmap: Bitmap? = null
    private var mOffscreenCanvas: Canvas? = null

    private val mMatrix = Matrix()
    private val mInvMatrix = Matrix()
    private var mDrawnLineSize = 0
    private var mSetuped = false

    private val mTmpPoints = FloatArray(2)

    // Set 0 for white and 255 for black pixel
    val pixelData: FloatArray?
        get() {
            if (mOffscreenBitmap == null) {
                return null
            }

            val width = mOffscreenBitmap!!.width
            val height = mOffscreenBitmap!!.height
            val pixels = IntArray(width * height)
            mOffscreenBitmap!!.getPixels(pixels, 0, width, 0, 0, width, height)

            val retPixels = FloatArray(pixels.size)
            for (i in pixels.indices) {
                val pix = pixels[i]
                val b = pix and 0xff
                retPixels[i] = ((0xff - b) / 255.0).toFloat()
            }
            return retPixels
        }

    fun setModel(model: DrawModel) {
        this.mModel = model
    }

    //reset the view, so empty the drawing (set everything to white and redraw the 28x28
    //rectangle
    fun reset() {
        mDrawnLineSize = 0
        if (mOffscreenBitmap != null) {
            mPaint.color = Color.WHITE
            val width = mOffscreenBitmap!!.width
            val height = mOffscreenBitmap!!.height
            mOffscreenCanvas!!.drawRect(Rect(0, 0, width, height), mPaint)
        }
    }

    //create the view, for a given length and width
    private fun setup() {
        mSetuped = true

        // View size
        val width = width.toFloat()
        val height = height.toFloat()

        // Model (bitmap) size
        val modelWidth = mModel!!.width.toFloat()
        val modelHeight = mModel!!.height.toFloat()

        val scaleW = width / modelWidth
        val scaleH = height / modelHeight

        var scale = scaleW
        if (scale > scaleH) {
            scale = scaleH
        }

        val newCx = modelWidth * scale / 2
        val newCy = modelHeight * scale / 2
        val dx = width / 2 - newCx
        val dy = height / 2 - newCy

        mMatrix.setScale(scale, scale)
        mMatrix.postTranslate(dx, dy)
        mMatrix.invert(mInvMatrix)
        mSetuped = true
    }

    public override//when the user begins drawing, initialize
            //the model renderer class and draw it on the canvas
    fun onDraw(canvas: Canvas) {
        if (mModel == null) {
            return
        }
        if (!mSetuped) {
            setup()
        }
        if (mOffscreenBitmap == null) {
            return
        }

        var startIndex = mDrawnLineSize - 1
        if (startIndex < 0) {
            startIndex = 0
        }

        DrawRenderer.renderModel(mOffscreenCanvas!!, mModel!!, mPaint, startIndex)
        canvas.drawBitmap(mOffscreenBitmap!!, mMatrix, mPaint)

        mDrawnLineSize = mModel!!.lineSize
    }

    /**
     * Convert screen position to local pos (pos in bitmap)
     */
    //calculates the position of the finger
    fun calcPos(x: Float, y: Float, out: PointF) {
        mTmpPoints[0] = x
        mTmpPoints[1] = y
        mInvMatrix.mapPoints(mTmpPoints)
        out.x = mTmpPoints[0]
        out.y = mTmpPoints[1]
    }

    fun onResume() {
        createBitmap()
    }

    fun onPause() {
        releaseBitmap()
    }

    //to draw the canvas we need the bitmap
    private fun createBitmap() {
        if (mOffscreenBitmap != null) {
            mOffscreenBitmap!!.recycle()
        }
        mOffscreenBitmap = Bitmap.createBitmap(mModel!!.width, mModel!!.height, Bitmap.Config.ARGB_8888)
        mOffscreenCanvas = Canvas(mOffscreenBitmap!!)
        reset()
    }

    private fun releaseBitmap() {
        if (mOffscreenBitmap != null) {
            mOffscreenBitmap!!.recycle()
            mOffscreenBitmap = null
            mOffscreenCanvas = null
        }
        reset()
    }
}
