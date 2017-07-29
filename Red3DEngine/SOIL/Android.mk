LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS :=

LOCAL_MODULE    := SOIL

LOCAL_SRC_FILES :=\
	image_DXT.c \
	SOIL.c \
	stb_image_aug.c \
	image_helper.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
