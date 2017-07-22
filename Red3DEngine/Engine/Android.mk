LOCAL_PATH := $(call my-dir)
#APP_PLATFORM := android-19
include $(CLEAR_VARS)

LOCAL_CFLAGS := -D__ANDROID__ -std=c++11 -fpermissive -Wno-write-strings

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../glm/

LOCAL_C_INCLUDES += ./Engine.hpp
LOCAL_C_INCLUDES += ./RedGame.hpp
LOCAL_C_INCLUDES += ./RedScipt.hpp

LOCAL_SRC_FILES += ./Camera.cpp
LOCAL_SRC_FILES += ./Light.cpp
LOCAL_SRC_FILES += ./Material.cpp
LOCAL_SRC_FILES += ./Mesh.cpp
LOCAL_SRC_FILES += ./Model.cpp

#$(warning $(LOCAL_SRC_FILES))
LOCAL_STATIC_LIBRARIES := GL

LOCAL_MODULE := Engine
include $(BUILD_STATIC_LIBRARY)
