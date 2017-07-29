LOCAL_PATH := $(call my-dir)
#APP_PLATFORM := android-19
include $(CLEAR_VARS)

LOCAL_CFLAGS := -D__ANDROID__ -std=c++11 -fpermissive -Wno-write-strings

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../

LOCAL_C_INCLUDES += ./File.hpp
LOCAL_C_INCLUDES += ./RedGL.hpp

LOCAL_SRC_FILES += ./GLProgram.cpp
LOCAL_SRC_FILES += ./GLShader.cpp
LOCAL_SRC_FILES += ./GLTexture.cpp
LOCAL_SRC_FILES += ./GLVAO.cpp
LOCAL_SRC_FILES += ./TextFile.cpp
LOCAL_SRC_FILES += ./ImageFile.cpp

#$(warning $(LOCAL_SRC_FILES))
LOCAL_STATIC_LIBRARIES += png
LOCAL_STATIC_LIBRARIES += SOIL

LOCAL_MODULE := GL
include $(BUILD_STATIC_LIBRARY)
