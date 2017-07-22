package com.redknot.red3dengineandroid;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity {

    private final int CONTEXT_CLIENT_VERSION = 3;
    private GLSurfaceView main_game_view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        setContentView(R.layout.activity_main);

        main_game_view = (GLSurfaceView)findViewById(R.id.main_game_view);


        if (detectOpenGLES30()) {
            main_game_view.setEGLContextClientVersion(CONTEXT_CLIENT_VERSION);
            main_game_view.setRenderer(new Red3DEngineRenderer(this));
        } else {
            Log.e("opengles30", "OpenGL ES 3.0 not supported on device.  Exiting...");
            finish();
        }
    }

    private boolean detectOpenGLES30() {
        ActivityManager am = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo info = am.getDeviceConfigurationInfo();

        return (info.reqGlEsVersion >= 0x30000);
    }
}
