package com.redknot.red3dengineandroid;

/**
 * Created by redknot on 22/07/2017.
 */

public class NativeMethod {
    static{
        System.loadLibrary("red3dengine");
    }

    public native static void Start();
    public native static void Update(int width,int height);
    public native static void End();
}
