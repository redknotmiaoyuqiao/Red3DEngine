#include "com_redknot_red3dengineandroid_NativeMethod.h"
#include "RedGameEngine.hpp"
/*
 * Class:     com_redknot_red3dengineandroid_NativeMethod
 * Method:    Start
 * Signature: ()V
 */

RedGame * redgame;

JNIEXPORT void JNICALL Java_com_redknot_red3dengineandroid_NativeMethod_Start
  (JNIEnv *, jclass)
  {
    redgame = new RedGame();
    redgame->Start();
  }

/*
 * Class:     com_redknot_red3dengineandroid_NativeMethod
 * Method:    Update
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_redknot_red3dengineandroid_NativeMethod_Update
  (JNIEnv *, jclass,int width,int height)
  {
    ScreenWidth = width;
    ScreenHeight = height;
    redgame->Update();
  }

/*
 * Class:     com_redknot_red3dengineandroid_NativeMethod
 * Method:    End
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_redknot_red3dengineandroid_NativeMethod_End
  (JNIEnv *, jclass)
  {
    redgame->End();
  }
