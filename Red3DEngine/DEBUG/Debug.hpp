#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>

#ifdef __ANDROID__
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#else
#include <GL/glew.h>
#endif

#ifdef __ANDROID__

#include <android/log.h>
#define LOG_TAG "opengl"
#define RedLog(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#else

#define RedLog(format, ...) printf(format, ##__VA_ARGS__)

#endif

#define glCheckError() glCheckError_(__FILE__, __LINE__)

using namespace std;

static string intToString(int v)
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "%u", v);

    string str = buf;
    return str;
}

static GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        char * error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        //std::cout << error << " | " << file << " (" << line << ")" << std::endl;

        RedLog("%s | %s (%d)\n",error,file,line);
    }
    return errorCode;
}

