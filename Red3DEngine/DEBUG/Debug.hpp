#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>

#ifdef __ANDROID__

#include <android/log.h>
#define LOG_TAG "opengl"
#define RedLog(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#else

#define RedLog(format, ...) printf(format, ##__VA_ARGS__)

#endif


using namespace std;

static string intToString(int v)
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "%u", v);

    string str = buf;
    return str;
}
