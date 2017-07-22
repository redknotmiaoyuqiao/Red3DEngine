package com.redknot.red3dengineandroid;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by redknot on 22/07/2017.
 */

public class Red3DEngineRenderer implements GLSurfaceView.Renderer {

    private Context context;

    private int width = 0;
    private int height = 0;

    public Red3DEngineRenderer(Context context){
        this.context = context;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeMethod.Start();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        this.width = width;
        this.height = height;

        NativeMethod.Update(this.width,this.height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        NativeMethod.Update(this.width,this.height);
    }
}
